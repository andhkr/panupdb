#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
constexpr size_t page_size  = 512;
constexpr uint max_count_of_page_in_cache = 5;
constexpr size_t database_cache_size =  max_count_of_page_in_cache*page_size;

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

private:
    int fd;
    std::string file_name;
};

struct cached_page{
    char _c_page[page_size]; /*cached page*/
    uint pid;   /*page identifier := table_idpage_id e.g if table_id := 3 
                and page_id := 8 then pid := 38*/
    bool dirty; /*is_modified*/
    void* next; /*pointer to next cached page*/ 
};

struct page_cache{
    void* cache_buffer = nullptr;
    uint count_page = 0;
    void* free_page_list = nullptr;
    page_cache(){
        int result = posix_memalign(&cache_buffer,page_size,(max_count_of_page_in_cache<<1));
        if(result){
            perror("memory allocation failed");
            exit(EXIT_FAILURE);
        }
        free_page_list = cache_buffer;
    }

    /*page replacement policy --> clock sweep algorithm*/
    void cache_in(cached_page* c_page){
        
    }

    void evict_page(uint pid){

    }

    cached_page* get_page(uint pid){

    }
};

