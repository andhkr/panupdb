#ifndef TABLE_HPP
#define TABLE_HPP

#include "../ast.hpp"
#include <unordered_map>

struct id_name{
    uint file_id=0;
    std::string file_name{};

    id_name()=default;
    id_name(uint,std::string);
    
    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_sizeof_object();
};

struct table_column{
    std::string column_name{};
    datatype* type=nullptr;
    bool nullable=true;
    bool has_default = false;
    datatype* dflt_value=nullptr;
    column_constraints* constraints=nullptr;
    uint total_constraints = 0;
    size_t total_object_size = 0;

    table_column()=default;

    table_column(column_definition* obj);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_sizeof_object();
};

struct table{
    std::string table_name{};
    std::vector<table_column*> columns{};
    std::vector<table_specific_constraints*> on_table_constraints{};
    /*used by query planar*/
    std::vector<std::vector<std::string>> columns_have_index{};
    uint column_cts;

    void print();
};

#endif