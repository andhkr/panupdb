#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

constexpr size_t page_size  = 512;
constexpr uint max_count_of_page_in_cache = 5;
constexpr size_t database_cache_size =  (max_count_of_page_in_cache<<1)*page_size;

struct page_header{
    size_t start_offset ; /*pointer of starting region of slot array*/
    size_t curr_offset ; /*end of slot array*/
    size_t free_space_start_marker ; /*pointer for start of free_space*/
    uint slot_counts = 0; /*number of slots == number of rows*/
    size_t free_list ; /*to maintain the list of node of fragmented free space*/
    /*for overflow pages*/;
    size_t overflowed_page_offset; 
    /*some checksum ,magic numbers added in future*/ 
    uint page_id = 0; /*it will be equivalen to page number 
                        so that it will be easy to seek*/
    page_header(){
        start_offset = sizeof(page_header);
        curr_offset  = sizeof(page_header);
        free_space_start_marker = page_size;
    }
};

struct slot{
    size_t row_offset;
    size_t size_of_row_data;
};

struct free_node{
    size_t next; /*next free node in list*/
    size_t size_of_node; /*size of free node*/
};

struct page{
    page_header header;
};
/*
sloted page will appear:
    header       slots       freespace               rows
|--------------|--|--|--|------------------|-------|-------|-------|
|              |  |  |  |                  |       |       |       |
|              |  |  |  |--->          <---|       |       |       |
|--------------|--|--|--|------------------|-------|-------|-------|
                |  |  |                        ^       ^       ^
                |  |  |------------------------|       |       |
                |  |-----------------------------------|       |
                |----------------------------------------------|

rows and slots will be in oder of insertion for data files.
*/

struct datafile_header{
    size_t magic_number; /* for file type, here for datafile: PaDBM */
    int page_counts;
    size_t free_page_list;
    uint table_id;
    /*checksums*/
};

/*
to perform all communication with disk
*/

/*utility function database specific*/
namespace padbm{
    bool is_little_endian(){
        int num = 1;
        char* ptr = (char*)&num;
        return ptr[0] == 1;
    }

    /*reverse byte order*/

    void reverse_byte(char* start,size_t size){
        char* right = start + size  - 1;
        while(start<right){
            std::swap(*start,*right);
            ++start;--right;
        }
    }
    /*when writing to disk*/
    void to_little_endian(char* start,size_t size){
        if(!is_little_endian()){
            reverse_byte(start,size);
        }
    }

    /*when reading from disk*/
    void to_native_endian(char* start,size_t size){
        /*since i am storing the data in data files always in little endian*/
        if(!is_little_endian()){
            reverse_byte(start,size);
        }
    }
}

struct disk_manager {

    disk_manager(std::string& file_name){
        file_name = file_name;
        fd = open(file_name.c_str(),O_RDWR | O_CREAT | O_DIRECT ,0666);
        if(fd == -1){
            perror("open failed");
            throw std::runtime_error("failed to open file");
        }
    }

    ~disk_manager(){
        if(fd != -1)close(fd);
    }

    void read(uint page_id,char* buffer){
        size_t offset = page_id*page_size;
        ssize_t bytes = pread(fd,buffer,page_size,offset);
        /*error check to implemented*/
    }

    void write(uint page_id,const char* buffer){
        size_t offset = page_id*page_size;
        ssize_t bytes = pwrite(fd,buffer,page_size,offset);
    }

    void close_file(){
        if(fd != -1)close(fd);
    }

private:
    int fd;
    std::string file_name;
};

struct cached_page_id{
    uint table_id;
    uint page_id;
    cached_page_id()=default;
    cached_page_id(uint table_id,uint page_id):table_id(table_id),page_id(page_id){}

    bool operator==(const cached_page_id& other) const {
        return table_id == other.table_id && page_id == other.page_id;
    }
};
namespace std {
    template <>
    struct hash<cached_page_id> {
        std::size_t operator()(const cached_page_id& pid) const noexcept {
            std::size_t h1 = std::hash<int>{}(pid.table_id);
            std::size_t h2 = std::hash<int>{}(pid.page_id);
            return h1 ^ (h2 << 1);  // combine hashes
        }
    };
}

struct cached_page{
    char _c_page[page_size]; /*cached page*/
    cached_page_id pid;
    bool dirty; /*is_modified*/
    cached_page* next; /*pointer to next cached page*/
    bool referenced; /*recently used*/ 

};

struct catalog_manager{
    /*lookup for table_id and  corresponding disk file name*/
    std::unordered_map<uint,std::string> tableid_filename_lookup;
};

catalog_manager cat_man;

/*page replacement policy --> clock sweep algorithm*/
struct clock_page_replacer{
    char * buffer_pool;
    bool count_page = 0;
    cached_page* page_list_head = nullptr;
    cached_page* page_list_tail = nullptr;
    cached_page* clock_handle = nullptr;

    clock_page_replacer()=default;

    clock_page_replacer(char* buffer_pool):buffer_pool(buffer_pool){
        page_list_head = (cached_page*)buffer_pool;
        page_list_tail = (cached_page*)buffer_pool;
        char* start  = nullptr;
        for(start = (char*)buffer_pool;(start+sizeof(cached_page))<=(((char*)buffer_pool+database_cache_size));start += sizeof(cached_page)){
            ((cached_page*)start)->next = (cached_page*)(start+sizeof(cached_page));
        }
        ((cached_page*)start)->next = nullptr;
    }

    cached_page* cache_in(uint table_id,uint page_id){
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
        new_page->pid.table_id = table_id;
        new_page->pid.page_id  = page_id;
        new_page->referenced   = true;
        return new_page;
    }

    cached_page* evict_page(){
        while(clock_handle->referenced){
            clock_handle->referenced = false;
            if(!clock_handle->next){
                clock_handle = page_list_head;
            }else{
                clock_handle = clock_handle->next;
            }
        }
        if(clock_handle->dirty){
            std::string filename = cat_man.tableid_filename_lookup[clock_handle->pid.table_id];
            disk_manager disk_man(filename);
            disk_man.write(clock_handle->pid.page_id,clock_handle->_c_page);
            disk_man.close_file();
        }        
        return clock_handle;
    }

    cached_page* evict_page(){
        while(clock_handle->referenced){
            clock_handle->referenced = false;
            if(!clock_handle->next){
                clock_handle = page_list_head;
            }else{
                clock_handle = clock_handle->next;
            }
        }
        if(clock_handle->dirty){
            std::string filename = cat_man.tableid_filename_lookup[clock_handle->pid.table_id];
            disk_manager disk_man(filename);
            disk_man.write(clock_handle->pid.page_id,clock_handle->_c_page);
            disk_man.close_file();
        }
        clock_handle = clock_handle->next;        
        return clock_handle;
    }

};


struct page_cache_manager{
    void* cache_buffer = nullptr;
    std::unordered_map<cached_page_id,cached_page*> page_lookup;
    clock_page_replacer page_replacer;

    page_cache_manager(){
        int result = posix_memalign(&cache_buffer,page_size,database_cache_size );
        if(result){
            perror("memory allocation failed");
            exit(EXIT_FAILURE);
        }
        page_replacer = clock_page_replacer(((char*)cache_buffer));
    }

    cached_page* get_page(uint table_id,uint page_id){
        if(page_lookup.find({table_id,page_id}) == page_lookup.end()){
            /*pid have table id and page id*/
            std::string filename = cat_man.tableid_filename_lookup[table_id];
            disk_manager disk_man(filename);
            cached_page* page_location_in_cache = page_replacer.cache_in(table_id,page_id);
            disk_man.read(page_id,page_location_in_cache->_c_page);
            disk_man.close_file();
            page_lookup[{table_id,page_id}] = page_location_in_cache;
            return page_location_in_cache;
        }else{
            cached_page* page = page_lookup[{table_id,page_id}];
            page->referenced = true;
            return page;
        }
    }
};


