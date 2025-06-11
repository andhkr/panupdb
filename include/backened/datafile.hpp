#ifndef DATAFILE_HPP
#define DATAFILE_HPP
#include <iostream>
#include <cstring>
#include "page.hpp"
#include "pandupdb_entity.hpp"

struct datafile_header{
    uint32_t magic_number=0; /* for file type, here for datafile: PaDBM */
    uint page_counts=0;
    uint row_counts=0;
    size_t free_page_list=1;
    uint table_id=0;
    /*schema of table i.e column sequence*/
    std::string table_name{};
    // std::vector<std::string> columns_names;
    /*checksums*/

    datafile_header();
    datafile_header(uint table_id,std::string& table_name);

    size_t serialise(char* buffer);
    size_t deserialise(const char * buffer);
};

#endif