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
extern std::unordered_map<uint,std::string> file_id_filename_lookup;

struct catalog_file_header{ /*for file_id and file_name lookup*/
    uint32_t magic_number;
    uint page_counts;
    size_t free_page_list;
    uint columns_ct; /* how many column in a table*/
    uint cat_id;

    catalog_file_header();
    catalog_file_header(uint cat_id);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_object_size();
};

enum file_type{
    INDEX,
    CATALOG,
    DATA
};

/*
page_id of header will be zero,
page_id will be increasing order and incresed by 1
*/
struct catalog_manager{
    std::string database_name;
    page_cache_manager buffer_pool_manager;
    /*file_id*/
    uint file_id = 0;
    std::unordered_map<std::string,table*> catalog_file_list;
    std::unordered_map<std::string,table*> index_file_root_list;

    /*load the file_id_filename_lookup hash table*/
    /*i am giving this file a special name id_name.cat*/
    catalog_manager();
    uint get_file_id();
    
    void load_file_lookup();

    /*it will table object initialised by query executor then catalog manager
    will create metadata file for this and write relevant data and then create datafile
    (file for data of table) and initilaise that header*/
    void create_table(table* obj);

    void load_catalog_file(uint file_id,std::string& table_name);

    void write_file_lookup();

    void database_query(std::string& cmd);
};

#endif