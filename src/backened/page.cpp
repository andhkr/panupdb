#include "include/backened/page.hpp"
#include <cstring>

page_header::page_header(uint p_id)
{
    free_space_start_marker = page_size;
    slot_counts = 0;
    free_list = page_size;
    overflowed_page_offset = 0;
    page_id = p_id;
    dead_page = false;
    next_free_page = 0;
    curr_offset  = sizeof(page_header);
    start_offset = sizeof(page_header);
}

size_t page_header::serialise(char* buffer){
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        memcpy(buffer,src,size);
        buffer += size;
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
    return sizeof(page_header); /*wrong need to edited*/
}
slot::slot(size_t offset,size_t data_size){
    row_offset = offset;
    size_of_row_data = data_size;
}

size_t slot::serialise(char* buffer){
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        memcpy(buffer,src,size);
        buffer += size;
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