#include "include/query_processor.hpp"

query_processor query_executor;

void query_processor::process_create_table(create_table* obj){
    table* tbl = new table;
    tbl->table_name = std::move(obj->table_name->identifier);
    std::vector<table_column*> columns;
    uint ct = 0;
    column_definition* curr = obj->columns_definitions;
    while(curr){
        table_column* col = new table_column(curr);
        columns.push_back(col);
        ct++;
        curr = (column_definition*)(((AST*)curr)->ptr_sibling);
    }
    tbl->columns = columns;
    tbl->column_cts = ct;

    catlg_man.create_table(tbl);
    return;
}