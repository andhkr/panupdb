#include "include/backened/disk_manager.hpp"
#include <filesystem>

/*
to perform all communication with disk
*/

/*utility function database specific*/
bool padbm::is_little_endian(){
    int num = 1;
    char* ptr = (char*)&num;
    return ptr[0] == 1;
}

/*reverse byte order*/
void padbm::reverse_byte(char* start,size_t size){
    char* right = start + size  - 1;
    while(start<right){
        std::swap(*start,*right);
        ++start;--right;
    }
}

/*when writing to disk*/
void padbm::to_little_endian(char* start,size_t size){
    if(!is_little_endian()){
        reverse_byte(start,size);
    }
}

/*when reading from disk*/
void padbm::to_native_endian(char* start,size_t size){
    /*since i am storing the data in data files always in little endian*/
    if(!is_little_endian()){
        reverse_byte(start,size);
    }
}

disk_manager::disk_manager(std::string& file_path){
    this->file_name = file_path;
    // 2. Open file using O_DIRECT
    fd = open(file_path.c_str(), O_RDWR | O_CREAT | O_DIRECT, 0666);
    if (fd == -1) {
        perror("open failed");
        throw std::runtime_error("Failed to open or create file with O_DIRECT: " + file_path);
    }
    // std::cout << "Opened file with O_DIRECT: " << full_path << "\n";
}

disk_manager::~disk_manager(){
    if(fd != -1)close(fd);
}

void disk_manager::read(uint page_id,char* buffer){
    std::memset(buffer,0,page_size);
    size_t offset = page_id*page_size;
    ssize_t bytes = pread(fd,buffer,page_size,offset);
    /*error check to implemented*/
    if(bytes<0){
        fprintf(stderr,"Data is Not Completely read please try again\n");
    }
}

void disk_manager::write(uint page_id,const char* buffer){
    size_t offset = page_id*page_size;
    ssize_t bytes = pwrite(fd,buffer,page_size,offset);
    /*error check to implemented*/
    if(bytes!=page_size){
        fprintf(stderr,"Incomplete Page Write Please try again");
    }
    fsync(fd);
}

void disk_manager::close_file(){
    if(fd != -1)close(fd);
}
cached_page_id::cached_page_id():file_id(0),page_id(0){}

cached_page_id::cached_page_id(uint file_id,uint page_id):file_id(file_id),page_id(page_id){}

/*for already present page*/
std::unordered_map<cached_page_id,cached_page*> page_lookup;
std::mutex page_lookup_lock;

void cached_page::pin_page(){
    page_lock.lock();
    pin_unpin = true;
};

void cached_page::unpin_page(){
    pin_unpin = false;
    page_lock.unlock();
}

/*page replacement policy --> clock sweep algorithm*/

clock_page_replacer::clock_page_replacer(char* buffer_pool):buffer_pool(buffer_pool){
    page_list_head = reinterpret_cast<cached_page*>(buffer_pool);
    page_list_tail = reinterpret_cast<cached_page*>(buffer_pool);
    char* start  = buffer_pool;
    for(;(start+(page_size<<1))<(buffer_pool+database_cache_size);start += (page_size<<1)){
        new (reinterpret_cast<void*>(start)) cached_page;
        reinterpret_cast<cached_page*>(start)->next = reinterpret_cast<cached_page*>(start+(page_size<<1));
    }
    new (reinterpret_cast<void*>(start)) cached_page;
    reinterpret_cast<cached_page*>(start)->next = nullptr;
}

cached_page* clock_page_replacer::cache_in(uint file_id,uint page_id){
    std::lock_guard<std::mutex> lk(page_replacer_lock);
    cached_page* new_page = nullptr;
    if(count_page == max_count_of_page_in_cache){
        new_page = evict_page();
    }
    else{
        new_page = page_list_tail;
        if(count_page==0){
            clock_handle = new_page;
        }
        page_list_tail = new_page->next;
        count_page++;
    }
    new_page->dirty = false;
    new_page->pid.file_id = file_id;
    new_page->pid.page_id  = page_id;
    new_page->referenced   = true;
    new_page->pin_page();
    return new_page;
}

cached_page* clock_page_replacer::evict_page(){
    while(clock_handle->referenced){
        clock_handle->referenced = false;
        if(clock_handle->pin_unpin){
            clock_handle->referenced = true;
        }
        if(!clock_handle->next){
            clock_handle = page_list_head;
        }else{
            clock_handle = clock_handle->next;
        }
    }

    if(clock_handle->dirty){
        std::string filename = file_id_filename_lookup[clock_handle->pid.file_id];
        disk_manager disk_man(filename);
        disk_man.write(clock_handle->pid.page_id,clock_handle->_c_page);
        disk_man.close_file();
    } 
    page_lookup.erase(clock_handle->pid);
    return clock_handle;
}

void clock_page_replacer::write_dirty_pages(){
    std::lock_guard<std::mutex> lk(page_replacer_lock);
    cached_page* curr = page_list_head;
    cached_page* prev = nullptr;
    while(curr){
        curr->pin_page();
        if(curr->dirty){
            std::string filename = file_id_filename_lookup[curr->pid.file_id];
            disk_manager disk_man(filename);
            disk_man.write(curr->pid.page_id,curr->_c_page);
            disk_man.close_file();
        }
        curr->unpin_page();
        prev = curr;
        curr = curr->next;
        prev->~cached_page();
    }
}

page_cache_manager::page_cache_manager(){
    int result = posix_memalign(&cache_buffer,page_size,database_cache_size);
    if(result){
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    page_replacer.~clock_page_replacer();
    new (&page_replacer) clock_page_replacer(((char*)cache_buffer));
}

cached_page* page_cache_manager::get_page(uint file_id,uint page_id){
    bool page_not_avail = true;
    {
        std::lock_guard<std::mutex> lk(page_lookup_lock);
        page_not_avail = page_lookup.find({file_id,page_id}) == page_lookup.end();
    }
    if(page_not_avail){
        /*pid have table id and page id*/
        std::string filename = file_id_filename_lookup[file_id];
        disk_manager disk_man(filename);
        cached_page* page_location_in_cache = page_replacer.cache_in(file_id,page_id);
        disk_man.read(page_id,page_location_in_cache->_c_page);
        disk_man.close_file();
        {
            std::lock_guard<std::mutex> lk(page_lookup_lock);
            page_lookup[{file_id,page_id}] = page_location_in_cache;
        }
        return page_location_in_cache;
    }else{
        cached_page* page = nullptr;
        {
            std::lock_guard<std::mutex> lk(page_lookup_lock);
            page = page_lookup[{file_id,page_id}];
        }
        page->pin_page();
        page->referenced = true;
        return page;
    }
}

void page_cache_manager::flush_all_pages(){
   page_replacer.write_dirty_pages();
}