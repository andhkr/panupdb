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

    catlg_man->create_table(tbl);
    return;
}

void query_processor::process_insert_stmt(insert_stmt* obj){
    /*step1:search table in which tuples will be inserted*/
    if(catlg_man->catalog_file_list.find(obj->table_name->identifier) != catlg_man->catalog_file_list.end()){
        /*step2: now check constraints for each column for data to be inserted */

        table* table = catlg_man->catalog_file_list[obj->table_name->identifier];
        uint NUM_CLMN = table->column_cts;
        
        std::vector<bool> nullbitmap(NUM_CLMN,true);
        std::vector<datatype*> values(NUM_CLMN,nullptr);

        if(obj->columns_to_insert){
            /*verifying the column constraints and creating NULLbitmap*/
            AST* colsptr = obj->columns_to_insert;
            AST* valuesptr = obj->values;
            while(colsptr){
                table_column* corresp_col = table->get_column_by_name(colsptr->identifier);
                int index = table->index_of_col(corresp_col->column_name);
                nullbitmap[index] = false;
                datatype* col_value = reinterpret_cast<datatype*>(valuesptr->ptr_children);
                corresp_col->check_constraints(col_value,table);
                values[index] = col_value;
                colsptr = colsptr->ptr_sibling;
                valuesptr = valuesptr->ptr_sibling;
            }
            /*issue disk write to catalog manager*/
            catlg_man->write_tuple_to_table(table, values,nullbitmap);
            table->tuples.push_back(values);
        }else{

        }

    }else{
        fprintf(stderr,"Table Does not exists\n");
        exit(EXIT_FAILURE);
    }
}

void query_processor::process_select_stmt(select_node* obj){
    catlg_man->catalog_file_list[obj->table_reference_list->first_table->identifier]->print_tuples();
    // tbl->print_tuples();
}

void query_processor::print_table(table* tbl){
    tbl->print_tuples();
}