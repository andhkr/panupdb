#include "include/backened/page.hpp"
#include <cstring>

page_header::page_header()
{
    free_space_start_marker = page_size;
    slot_counts = 0;
    free_list = page_size;
    overflowed_page_offset = 0;
    page_id = 0;
    dead_page = false;
    next_free_page = 0;
    curr_offset  = get_sizeof_object();
    start_offset = get_sizeof_object();
}

page_header::page_header(uint p_id)
{
    free_space_start_marker = page_size;
    slot_counts = 0;
    free_list = page_size;
    overflowed_page_offset = 0;
    page_id = p_id;
    dead_page = false;
    next_free_page = 0;
    curr_offset  = get_sizeof_object();
    start_offset = get_sizeof_object();
}

size_t page_header::serialise(char* buffer){
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        if(offset>page_size){
            std::cout<<"page_header_serialisation failed"<<
            offset<<" "<<page_size<<std::endl;
        }
        memcpy(buffer+offset,src,size);
        offset += size;
    };

    write(&free_space_start_marker,sizeof(free_space_start_marker));
    write(&slot_counts,sizeof(slot_counts));
    write(&free_list,sizeof(free_list));
    write(&overflowed_page_offset,sizeof(overflowed_page_offset));
    write(&page_id,sizeof(page_id));
    write(&dead_page,sizeof(dead_page));
    write(&next_free_page,sizeof(next_free_page));
    write(&curr_offset,sizeof(curr_offset));
    write(&start_offset,sizeof(start_offset));
    return offset;
}

size_t page_header::deserialise(const char* buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset+=size;
    };
   
    read(&free_space_start_marker,sizeof(free_space_start_marker));
    read(&slot_counts,sizeof(slot_counts));
    read(&free_list,sizeof(free_list));
    read(&overflowed_page_offset,sizeof(overflowed_page_offset));
    read(&page_id,sizeof(page_id));
    read(&dead_page,sizeof(dead_page));
    read(&next_free_page,sizeof(next_free_page));
    read(&curr_offset,sizeof(curr_offset));
    read(&start_offset,sizeof(start_offset));
    return offset;
}

size_t page_header::get_sizeof_object(){   
    size_t offset = 0;
    offset += sizeof(size_t); /*pointer for start of free_space*/
    offset += sizeof(uint); /*number of slots == number of rows*/
    offset += sizeof(size_t); /*to maintain the list of node of fragmented free space*/
    /*for overflow pages*/;
    offset += sizeof(size_t); 
    /*some checksum ,magic numbers added in future*/ 
    offset += sizeof( uint) ; /*it will be equivalen to page number 
                        so that it will be easy to seek*/
    offset += sizeof(bool); /*that is this page is deleted*/
    offset += sizeof(size_t);
    offset += sizeof(size_t); /*end of slot array*/
    offset += sizeof(size_t);
    return offset;
}

slot::slot():row_offset(page_size),size_of_row_data(page_size){}

slot::slot(size_t offset,size_t data_size){
    this->row_offset = offset;
    this->size_of_row_data = data_size;
}

size_t slot::serialise(char* buffer){
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        if(offset>page_size){
            std::cout<<"slot_serialisation failed"<<
            offset<<" "<<page_size<<std::endl;
        }
        memcpy(buffer+offset,src,size);
        offset += size;
    };

    write(&row_offset,sizeof(row_offset));
    write(&size_of_row_data,sizeof(size_of_row_data));

    return offset;
}

size_t slot::deserialise(const char* buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset+=size;
    };

    read(&row_offset,sizeof(row_offset));
    read(&size_of_row_data,sizeof(size_of_row_data));
    
    return offset;
}

size_t slot::get_sizeof_object(){
    return sizeof(row_offset) + sizeof(size_of_row_data);
}

size_t slot::get_sizeof_slot_obj(){
    return sizeof(row_offset) + sizeof(size_of_row_data);
}