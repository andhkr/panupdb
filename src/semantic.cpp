#include "include/semantic.hpp"
#include "include/backened/catalog_manager.hpp"

semantic_error::semantic_error(const std::string& m) : msg(m) {}
/*copy constructor*/
semantic_error::semantic_error(const semantic_error& other):msg(other.msg){}
/*copy assignment constructor*/
semantic_error& semantic_error::operator=(const semantic_error& other){
        if(this != &other){
            msg = other.msg;
        }
        return *this;
}

const char* semantic_error::what() const noexcept { return msg.c_str(); }



extern catalog_manager* catlg_man;
/* when try to fetching the data from table*/
void semantic_analyser::check_table_existence(std::string& table_name){
    if(catlg_man->catalog_file_list.find(table_name) == catlg_man->catalog_file_list.end()){
        throw semantic_error("Error: Table "+table_name+" not exists");
    }
}

/* when try to making the table*/
void semantic_analyser::check_table_already_present(std::string& table_name){
    if(catlg_man->catalog_file_list.find(table_name) != catlg_man->catalog_file_list.end()){
        throw semantic_error("Error: Table "+table_name+" already exists");
    }
}

/*when try to get columns data*/
void semantic_analyser::check_column_existence(std::string& table_name,std::string& column_name){
    if(!catlg_man->catalog_file_list[table_name]->column_present(column_name)){
        throw semantic_error("Error: Column " +column_name+ " in table "+table_name+" does not exists");
    }
}

semantic_analyser semantic_analysis;
