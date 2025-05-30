#ifndef CATALOG_MANAGER_HPP
#define CATALOG_MANAGER_HPP

#include <iostream>
#include <vector>
#include "../datatypes.hpp"
#include "disk_manager.hpp"
#include "page.hpp"
#include "../ast.hpp"
#include "table.hpp"
#include "pandupdb_entity.hpp"
#include "datafile.hpp"
#include <unordered_map>
/*
database will have list of tables 
*/
struct database{
    std::string database_name;
    std::unordered_map<std::string,table*> table_list;
};

struct catalog_file_header{ /*for file_id and file_name lookup*/
    uint32_t magic_number;
    uint page_counts;
    size_t free_page_list;
    uint columns_ct; /* how many column in a table*/
    uint cat_id;

    catalog_file_header()=default;
    catalog_file_header(uint cat_id);

    void serialise(char* buffer);

    void deserialise(const char* buffer);

    size_t get_total_object_size();
};

struct id_name{
    uint file_id;
    std::string file_name;
};

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

    std::unordered_map<std::string,table*> table_list;
    /*load the file_id_filename_lookup hash table*/
    /*i am giving this file a special name id_name.cat*/
    catalog_manager();

    void load_file_lookup();

    /*it will table object initialised by query executor then catalog manager
    will create metadata file for this and write relevant data and then create datafile
    (file for data of table) and initilaise that header*/
    void create_table(table* obj);

    uint get_file_id();

    // void write_file_lookup();

    void database_query(std::string& cmd);

};

#endif