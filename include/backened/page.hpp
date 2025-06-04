#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <unordered_map>

constexpr size_t page_size  = 512;
constexpr uint max_count_of_page_in_cache = 5;
constexpr size_t database_cache_size =  (max_count_of_page_in_cache<<1)*page_size;

struct page_header{
    size_t free_space_start_marker; /*pointer for start of free_space*/
    uint slot_counts = 0; /*number of slots == number of rows*/
    size_t free_list ; /*to maintain the list of node of fragmented free space*/
    /*for overflow pages*/;
    size_t overflowed_page_offset; 
    /*some checksum ,magic numbers added in future*/ 
    uint page_id = 0; /*it will be equivalen to page number 
                        so that it will be easy to seek*/
    bool dead_page = false ; /*that is this page is deleted*/
    size_t next_free_page;
    size_t curr_offset ; /*end of slot array*/
    size_t start_offset ; /*pointer of starting region of slot array*/
    page_header();
    page_header(uint p_id);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_sizeof_object();
};

struct slot{
    size_t row_offset;
    size_t size_of_row_data;
    slot();
    slot(size_t,size_t);

    size_t serialise(char* buffer);
    size_t deserialise(const char* buffer);
    size_t get_sizeof_object();
    
    static size_t get_sizeof_slot_obj();
};

struct free_node{
    size_t next; /*next free node in list*/
    size_t size_of_node; /*size of free node*/
};

// struct page{
//     page_header header;
// };
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


#endif