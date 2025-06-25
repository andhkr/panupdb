#ifndef DISK_MANAGER_HPP
#define DISK_MANAGER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include "page.hpp"
#include <functional>  // for std::hash
#include <thread>
#include <mutex>

extern std::unordered_map<uint,std::string> file_id_filename_lookup;
/*
to perform all communication with disk
*/
/*utility function database specific*/
namespace padbm{
    bool is_little_endian();
    /*reverse byte order*/
    void reverse_byte(char* start,size_t size);
    /*when writing to disk*/
    void to_little_endian(char* start,size_t size);
    /*when reading from disk*/
    void to_native_endian(char* start,size_t size);

}

struct disk_manager {

    disk_manager(std::string& file_name);

    ~disk_manager();

    void read(uint page_id,char* buffer);

    void write(uint page_id,const char* buffer);

    void close_file();

private:
    int fd;
    std::string file_name;
};

// #pragma once
struct cached_page_id{
    uint file_id;
    uint page_id;
    cached_page_id();
    cached_page_id(uint file_id,uint page_id);
    bool operator==(const cached_page_id& other) const {
        return file_id == other.file_id && page_id == other.page_id;
    }
};

// Specialize std::hash so cached_page_id can be used in unordered_map/set
namespace std {
    template <>
    struct hash<cached_page_id> {
        std::size_t operator()(const cached_page_id& pid) const noexcept {
            std::size_t h1 = std::hash<int>{}(pid.file_id);
            std::size_t h2 = std::hash<int>{}(pid.page_id);
            return h1 ^ (h2 << 1);  // Combine the hashes
        }
    };
}

struct cached_page{
    char _c_page[page_size]; /*cached page*/
    cached_page_id pid;
    bool dirty=false; /*is_modified*/
    cached_page* next=nullptr; /*pointer to next cached page*/
    bool referenced=false; /*recently used*/ 
    bool pin_unpin = false;/*currently in use by a component or not*/
    std::mutex page_lock;
    
    cached_page()=default;
    void pin_page();
    void unpin_page();
};

/*page replacement policy --> clock sweep algorithm*/
struct clock_page_replacer{
    char * buffer_pool=nullptr;
    int count_page = 0;
    cached_page* page_list_head = nullptr;
    cached_page* page_list_tail = nullptr;
    cached_page* clock_handle = nullptr;
    std::mutex page_replacer_lock;

    clock_page_replacer()=default;

    explicit clock_page_replacer(char* buffer_pool);

    cached_page* cache_in(uint file_id,uint page_id);

    cached_page* evict_page();
};

struct page_cache_manager{
    void* cache_buffer = nullptr;
    clock_page_replacer page_replacer;

    page_cache_manager();

    cached_page* get_page(uint file_id,uint page_id);

    void flush_all_pages();
};

#endif

