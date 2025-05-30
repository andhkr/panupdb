#include "include/backened/catalog_manager.hpp"

catalog_manager catlg_man;
std::string file_id_filename_hash_table = "id_name.cat";
/*for file_id and file_name lookup*/
catalog_file_header::catalog_file_header(uint cat_id){
    magic_number = Magic_Number::CATALOG;
    page_counts = 0;
    free_page_list = page_size;
    columns_ct = 0;
    this->cat_id = cat_id;
}

void catalog_file_header::serialise(char* buffer){
    auto write = [&](void* src,size_t size){
        memcpy(buffer,src,size);
        buffer += size;
    };

    write(&magic_number,sizeof(magic_number));
    write(&page_counts,sizeof(page_counts));
    write(&free_page_list,sizeof(free_page_list));
    write(&columns_ct,sizeof(columns_ct));
    write(&cat_id,sizeof(cat_id));
}

void catalog_file_header::deserialise(const char* buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset+=size;
    };
    read(&magic_number,sizeof(magic_number));
    read(&page_counts,sizeof(page_counts));
    read(&free_page_list,sizeof(free_page_list));
    read(&columns_ct,sizeof(columns_ct));
    read(&cat_id,sizeof(cat_id));
}

size_t catalog_file_header::get_total_object_size(){
    size_t total = sizeof(magic_number); 
    total+= sizeof(page_counts);
    total+= sizeof(free_page_list);
    total+= sizeof(columns_ct);
    total+= sizeof(cat_id);
    return total;
}

/*
page_id of header will be zero,
page_id will be increasing order and incresed by 1
*/

catalog_manager::catalog_manager(){
    file_id_filename_lookup[0]=file_id_filename_hash_table;
    load_file_lookup();
}

void catalog_manager::load_file_lookup(){
    cached_page* c_header = buffer_pool_manager.get_page(0,0);
    char* ptr = c_header->_c_page;
    memcpy(&(cat_file_head.magic_number),ptr,sizeof(size_t));
    ptr += sizeof(size_t);
    memcpy(&(cat_file_head.page_counts),ptr,sizeof(uint));
    ptr += sizeof(uint);
    memcpy(&(cat_file_head.free_page_list),ptr,sizeof(size_t));
    uint page_cnts = cat_file_head.page_counts;
    int page_id = 1;

    while(page_cnts--){
        cached_page* c_page = buffer_pool_manager.get_page(0,page_id);
        /*not consedering overflowed_pages*/
        size_t start_offset;
        ptr = c_page->_c_page;
        memcpy(&start_offset,ptr,sizeof(size_t));
        size_t curr_offset;
        memcpy(&curr_offset,ptr+sizeof(size_t),sizeof(size_t));
        char* end = ptr+curr_offset;
        ptr = ptr+start_offset; /* pointing the start of slot array*/
        while(ptr != end){
            slot pos_of_id_name;
            memcpy(&pos_of_id_name.row_offset,ptr,sizeof(size_t));
            char* row;
            ptr = ptr+sizeof(size_t);
            memcpy(&pos_of_id_name.size_of_row_data,ptr,sizeof(size_t));
            ptr = ptr + sizeof(size_t); /*now ptr is at next row*/
            id_name fileid_filename;
            row = c_page->_c_page+pos_of_id_name.row_offset;
            memcpy(&fileid_filename.file_id,row,sizeof(uint));
            row += sizeof(uint);
            size_t len;
            memcpy(&len,row,sizeof(size_t));
            fileid_filename.file_name.resize(len);
            row += sizeof(len);
            memcpy(&fileid_filename.file_name[0],row,len); 
            file_id_filename_lookup[fileid_filename.file_id] = fileid_filename.file_name;
        }
    }
}

/*it will table object initialised by query executor then catalog manager
will create metadata file for this and write relevant data and then create datafile
(file for data of table) and initilaise that header*/
void catalog_manager::create_table(table* obj){
    /*datafile creation and saved*/
    uint d_id = get_file_id();
    std::string datafile_name = obj->table_name + ".df";
    file_id_filename_lookup[d_id] = datafile_name;
    cached_page* header = buffer_pool_manager.get_page(d_id,0);
    header->dirty = true;
    datafile_header data_hdr(d_id,obj->table_name);
    data_hdr.serialise(header->_c_page);

    /*meta data updates*/
    uint c_id = get_file_id();
    file_id_filename_lookup[c_id] =    obj->table_name + ".ct";
    cached_page* ct_header = buffer_pool_manager.get_page(c_id,0);
    ct_header->dirty = true;
    catalog_file_header cat_file(c_id);
    if(cat_file.get_total_object_size()<=page_size){
        cat_file.serialise(ct_header->_c_page);
    }

    /*adding column name and constraint*/
    uint number_of_clmns = obj->column_cts;
    uint page_id = 1;
    size_t i = 0;
    new_page:
        cached_page* c_page = buffer_pool_manager.get_page(c_id,page_id++);
        c_page->dirty = true;
        page_header hdr(page_id);
        char* buffer = c_page->_c_page;
        size_t bytes_written = hdr.get_sizeof_object();
        hdr.curr_offset = bytes_written;
        hdr.start_offset = bytes_written;

        for(;i<obj->columns.size();++i){
            table_column* curr = obj->columns[i];
            size_t size_of_row = curr->get_total_sizeof_object();
            if((sizeof(slot)+size_of_row)<=(hdr.free_space_start_marker - hdr.curr_offset)){
                size_t offset = hdr.free_space_start_marker - size_of_row;
                buffer = c_page->_c_page + offset;
                curr->serialise(buffer);
                slot row_metadata(offset,size_of_row);
                buffer = c_page->_c_page + hdr.curr_offset;
                size_t slot_offset = row_metadata.serialise(buffer);
                hdr.free_space_start_marker = offset;
                hdr.curr_offset = slot_offset;

            }else{
                /*unpin the page allocate new page */
                size_t bytes_written = hdr.serialise(buffer);
                goto new_page;
                /*overflow is not handeled here for time being*/
            }
        }
}
uint catalog_manager::get_file_id(){
    uint id = file_id;
    ++file_id;
    return id;
}

void catalog_manager::database_query(std::string& cmd){
    if(cmd.substr(0,2)=="/d"){
        std::string table_name = cmd.substr(2);
        table* tbl = table_list[table_name];
        tbl->print();
    }
}

