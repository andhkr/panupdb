#include "include/backened/datafile.hpp"

datafile_header::datafile_header(uint table_id,std::string& table_name){
    magic_number = Magic_Number::DATA;
    page_counts = 0;
    row_counts = 0;
    free_page_list = page_size;
    this->table_id = table_id;
    this->table_name = table_name;
}

void datafile_header::serialise(char* buffer){

    auto write = [&](void* src,size_t size){
        memcpy(buffer,src,size);
        buffer += size;
    };

    write(&magic_number,sizeof(magic_number));
    write(&page_counts,sizeof(page_counts));
    write(&row_counts,sizeof(row_counts));
    write(&free_page_list,sizeof(free_page_list));
    write(&table_id,sizeof(table_id));
    /*writing string name*/
    size_t size = table_name.size();
    write(&size,sizeof(size));
    write(table_name.data(),size);
}

void datafile_header::deserialise(const char * buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset += size;
    };

    read(&magic_number,sizeof(magic_number));
    read(&page_counts,sizeof(page_counts));
    read(&row_counts,sizeof(row_counts));
    read(&free_page_list,sizeof(free_page_list));
    read(&table_id,sizeof(table_id));
    /*readingstring name*/
    size_t size = 0;
    read(&size,sizeof(size));
    table_name.resize(size);
    read(&table_name[0],size);
}