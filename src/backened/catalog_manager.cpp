#include <iostream>
#include <vector>
#include "include/datatypes.hpp"
#include "include/disk_manager.hpp"
#include "include/page.hpp"
#include "include/ast.hpp"

std::string file_id_filename_hash_table = "id_name.cat";

struct table_specific_constraints{

};

struct table_column{
    std::string column_name;
    datatype* type;
    bool nullable=true;
    datatype* dflt_value;
    column_constraints* constraints;
    size_t total_object_size = 0;

    table_column()=default;

    size_t serialise(char* buffer){
        size_t total_obj_size = get_total_sizeof_object();
        auto write = [&](void* src,size_t size){
            memcpy(buffer,src,size);
            buffer += size;
        };

        size_t column_name_len = column_name.size();

        write(&column_name_len,sizeof(column_name_len));
        write(column_name.data(),column_name_len);
        size_t bytes_written = type->serialise(buffer);
        buffer += bytes_written;
        write(&nullable,sizeof(nullable));
        buffer += dflt_value->serialise(buffer);

        column_constraints* curr = constraints;
        while(curr){
            buffer+= constraints->serialise(buffer);
            curr = curr->next_constraint;
        }

        write(&total_object_size,sizeof(total_obj_size));

        return get_total_sizeof_object();
    }

    size_t deserialise(const char* buffer){
        size_t offset = 0;

        auto read = [&](void* dest,size_t size){
            memcpy(dest,buffer+offset,size);
            offset += size;
        };

        size_t column_name_len = 0;

        read(&column_name_len,sizeof(column_name_len));
        column_name.resize(column_name_len);
        read(&column_name[0],column_name_len);
        size_t bytes_written = type->deserialise(buffer+offset);
        offset += bytes_written;
        read(&nullable,sizeof(nullable));
        offset += dflt_value->deserialise(buffer+offset);

        column_constraints* curr = constraints;
        while(curr){
            offset+= constraints->deserialise(buffer+offset);
            curr = curr->next_constraint;
        }

        read(&total_object_size,sizeof(total_object_size));
        return get_total_sizeof_object();
    }

    size_t get_total_sizeof_object(){
        if(total_object_size) return total_object_size;
        size_t total = 0;
        total+= sizeof(total_object_size);
        total+= sizeof(size_t) + column_name.size();
        total+= type->get_total_object_size();
        total+= sizeof(nullable);
        total+= dflt_value->get_total_object_size();
        column_constraints* curr = constraints;
        while(curr){
            if(constraints->constrt_type()==NOT_NULL){
                nullable = false;
            }
            else if(curr->constrt_type()==DEFAULT_VALUE){
                dflt_value = static_cast<default_value*>(curr)->value;
            }
            total+= constraints->get_total_sizeof_object();
            curr = curr->next_constraint;
        }
        return total_object_size = total;
    }


};

struct table{
    std::string table_name;
    std::vector<table_column*> columns;
    std::vector<table_specific_constraints*> on_table_constraints;
    /*used by query planar*/
    std::vector<std::vector<std::string>> columns_have_index;
    uint column_cts;
};

/*
database will have list of tables 
*/
struct database{
    std::string database_name;
    std::vector<table*> table_list;
};

struct datafile_header{
    size_t magic_number; /* for file type, here for datafile: PaDBM */
    uint page_counts;
    uint row_counts;
    size_t free_page_list;
    uint table_id;
    /*schema of table i.e column sequence*/
    std::string table_name;
    // std::vector<std::string> columns_names;
    /*checksums*/

    datafile_header()=default;
    datafile_header(uint table_id,std::string& table_name){
        magic_number = Magic_Number::DATA;
        page_counts = 0;
        row_counts = 0;
        free_page_list = page_size;
        this->table_id = table_id;
        this->table_name = table_name;
    }

    void serialise(char* buffer){

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

    void deserialise(const char * buffer){
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
};

enum index_type{
    BTREE,
    HASH,
    GIN,
    COVERING
};

struct index_file_header{
    size_t magic_number; /* for file type, here for datafile: PaDBM */
    index_type type;
    uint page_counts;
    size_t free_page_list;
    uint index_id; 
    /* i.e columns in index*/
    std::vector<std::string> columns_names;
    /*checksums*/
};

struct catalog_file_header{ /*for file_id and file_name lookup*/
    uint32_t magic_number;
    uint page_counts;
    size_t free_page_list;
    uint columns_ct; /* how many column in a table*/
    uint cat_id;

    catalog_file_header()=default;
    catalog_file_header(uint cat_id){
        magic_number = Magic_Number::CATALOG;
        page_counts = 0;
        free_page_list = page_size;
        columns_ct = 0;
        this->cat_id = cat_id;
    }

    void serialise(char* buffer){
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

    void deserialise(const char* buffer){
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

    size_t get_total_object_size(){
        size_t total = sizeof(magic_number); 
        total+= sizeof(page_counts);
        total+= sizeof(free_page_list);
        total+= sizeof(columns_ct);
        total+= sizeof(cat_id);
        return total;
    }
};

struct id_name{
    uint file_id;
    std::string file_name;
};


namespace Magic_Number {

    constexpr uint32_t make_magic(const char tag[4]) {
        return (static_cast<uint32_t>(tag[0]) << 24) |
               (static_cast<uint32_t>(tag[1]) << 16) |
               (static_cast<uint32_t>(tag[2]) << 8)  |
               (static_cast<uint32_t>(tag[3]));
    }

    constexpr uint32_t DATA    = make_magic("DBDF");
    constexpr uint32_t INDEX   = make_magic("DBIF");
    constexpr uint32_t CATALOG = make_magic("DBCT");

}

/*
page_id of header will be zero,
page_id will be increasing order and incresed by 1
*/
struct catalog_manager{
    std::string database_name;
    /*lookup for file_id and  corresponding disk file name*/
    std::unordered_map<uint,std::string> file_id_filename_lookup;
    page_cache_manager buffer_pool_manager;
    catalog_file_header cat_file_head;
    /*file_id*/
    uint file_id ;

    /*load the file_id_filename_lookup hash table*/
    /*i am giving this file a special name id_name.cat*/
    catalog_manager()=default;
    catalog_manager(){
        file_id_filename_lookup[0]=file_id_filename_hash_table;
        load_file_lookup();
    }

    void load_file_lookup(){
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
                memcpy(&fileid_filename.file_name,row,pos_of_id_name.size_of_row_data-sizeof(uint)); 
                file_id_filename_lookup[fileid_filename.file_id] = fileid_filename.file_name;
            }
        }
    }

    /*it will table object initialised by query executor then catalog manager
    will create metadata file for this and write relevant data and then create datafile
    (file for data of table) and initilaise that header*/
    void create_table(table* obj){
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
        int i = 0;
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
    uint get_file_id(){
        uint id = file_id;
        ++file_id;
        return id;
    }
};



/*
sloted page for fileid_filename_lookup file will appear:
    header       slots       freespace         struct id_name
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
