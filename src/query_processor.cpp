#include "include/query_processor.hpp"
#include "include/select_plan.hpp"
#include "include/semantic.hpp"
#include <sstream>

query_processor query_executor;

void query_processor::process_create_table(create_table* obj){
try{    
    semantic_analysis.check_table_already_present(obj->table_name->identifier);   
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
}catch(const semantic_error& e){
    std::cout<<e.what()<<std::endl;
}
}

void query_processor::process_insert_stmt(insert_stmt* obj){
try{
    semantic_analysis.check_table_existence(obj->table_name->identifier);

    table* table = catlg_man->catalog_file_list[obj->table_name->identifier];
    uint NUM_CLMN = table->column_cts;
    
    std::vector<bool> nullbitmap(NUM_CLMN,true);
    std::vector<std::vector<datatype*>> values;

    if(obj->columns_to_insert){
        /*verifying the column constraints and creating NULLbitmap*/
        AST* colsptr = obj->columns_to_insert;

        std::vector<int> colindex;

        while(colsptr){
            semantic_analysis.check_column_existence(table->table_name,colsptr->identifier);
            table_column* corresp_col = table->get_column_by_name(colsptr->identifier);
            int index = table->index_of_col(corresp_col->column_name);
            nullbitmap[index] = false;
            colsptr = colsptr->ptr_sibling;
            colindex.push_back(index);
        }


        AST* valuesptr = obj->values;
        while(valuesptr){
            AST* tuple = valuesptr->ptr_children;
            std::vector<datatype*> value(NUM_CLMN,nullptr);
            int i = 0;
            while(tuple){
                datatype* col_value = reinterpret_cast<datatype*>(tuple->ptr_children);
                value[colindex[i]] = col_value;
                ++i;
                tuple = tuple->ptr_sibling;    
            }
            values.push_back(value);
            for(uint i = 0;i<table->column_cts;++i){
                table->columns[i]->check_constraints(value[i],table);
            }
            valuesptr = valuesptr->ptr_sibling;
        }
        
        /*issue disk write to catalog manager*/
        catlg_man->write_tuple_to_table(table, values, nullbitmap);
        // table->tuples.push_back(values);
        }else{

        }
}catch (const semantic_error& e){
    std::cout<<e.what()<<std::endl;
}
}

void print_val(std::future<batch>&& res);

std::mutex cout_mtx;

void query_processor::process_select_stmt(select_node* obj){
try{
    logical_op_uptr loptr = get_logical_ast(obj);
    physical_op_uptr phy_root = query_planner::plan(loptr.get());

    project_op* root = static_cast<project_op*>(phy_root.get());
    std::cout<<std::endl;
    for(size_t i = 0;i<root->clmns.size();++i){
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
    // delete obj;
}catch (const semantic_error& e ){
    std::cout<<e.what()<<std::endl;
}
}

void print_val(std::future<batch>&& res){
    batch tpls  = res.get();
    std::stringstream ss;
    for(size_t i = 0;i<tpls.size();++i){
        for(auto& v : tpls[i]){
            switch(v->get_type()){
                case INT:{
                    ss<<static_cast<inttype*>(v)->value<<"     ";
                }
                break;
                case VARCHAR:{
                    ss<<static_cast<varchar*>(v)->value<<"     ";
                    break;
                }default:{
                    break;
                }
            }
            delete v;
            v = nullptr;
        }
        ss<<std::endl;
    }
    
    {
        std::lock_guard<std::mutex> lk(cout_mtx);
        std::string result = ss.str();
        std::cout<<result;
    }
}

void query_processor::print_table(table* tbl){
    tbl->print_tuples();
}

