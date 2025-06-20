#include "include/query_processor.hpp"
#include "include/select_plan.hpp"

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
                values[index] = col_value;
                colsptr = colsptr->ptr_sibling;
                valuesptr = valuesptr->ptr_sibling;
            }

            for(uint i = 0;i<table->column_cts;++i){
                table->columns[i]->check_constraints(values[i],table);
            }
            /*issue disk write to catalog manager*/
            catlg_man->write_tuple_to_table(table, values, nullbitmap);
            table->tuples.push_back(values);
        }else{

        }

    }else{
        fprintf(stderr,"Table Does not exists\n");
        exit(EXIT_FAILURE);
    }
}

void print_val(std::future<batch>&& res);

void query_processor::process_select_stmt(select_node* obj){

    logical_op_uptr loptr = get_logical_ast(obj);
    physical_op_uptr phy_root = query_planner::plan(loptr.get());

    project_op* root = static_cast<project_op*>(phy_root.get());
    for(int i = 0;i<root->clmns.size();++i){
        std::cout<<root->clmns[i]<<"     ";
    }
    std::cout<<std::endl;

    std::vector<std::future<void>> print_val_future;
    bool flag = true;
    while(flag){

        std::future<batch> result;
        flag = phy_root->next(result);
        
        if(!flag) break;
        std::future<void> print_future = worker_threads.submit_task(
            [result = std::move(result)]() mutable {
                return print_val(std::move(result));
            }
        );

        print_val_future.push_back(std::move(print_future));
        
    }

    for(auto& print_future:print_val_future){
        print_future.get();
    }
}

void print_val(std::future<batch>&& res){
    batch tpls  = res.get();
    for(int i = 0;i<tpls.size();++i){
        for(auto& v : tpls[i]){
            switch(v->get_type()){
                case INT:{
                    std::cout<<static_cast<inttype*>(v)->value<<"     ";
                }
                break;
                case VARCHAR:{
                    std::cout<<static_cast<varchar*>(v)->value<<"     ";
                    break;
                }default:{
                    break;
                }
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"called"<<std::endl;
}
void query_processor::print_table(table* tbl){
    tbl->print_tuples();
}

