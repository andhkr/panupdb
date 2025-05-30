#ifndef INDEX_FILE_HPP
#define INDEX_FILE_HPP

#include <iostream>
#include <vector>
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

#endif