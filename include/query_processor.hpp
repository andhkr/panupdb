#ifndef QUERY_PROCESSOR_HPP
#define QUERY_PROCESSOR_HPP
#include "ast.hpp"
#include "constraints.hpp"
#include "backened/table.hpp"
#include "backened/catalog_manager.hpp"
// #include "datatypes.hpp"

struct query_processor{

    query_processor()=default;

    void process_create_table(create_table* obj);

    void process_insert_stmt(insert_stmt* obj);

    void process_select_stmt(select_node* obj);

    void print_table(table*);
    
};


extern query_processor query_executor;
extern catalog_manager* catlg_man;
#endif