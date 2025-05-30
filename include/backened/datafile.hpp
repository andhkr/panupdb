#ifndef DATAFILE_HPP
#define DATAFILE_HPP
#include <iostream>
#include <cstring>
#include "page.hpp"
#include "pandupdb_entity.hpp"

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
    datafile_header(uint table_id,std::string& table_name);

    void serialise(char* buffer);
    void deserialise(const char * buffer);
};
#endif