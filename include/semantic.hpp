#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include <exception>
#include <string>
#include "ast.hpp"

class semantic_error : public std::exception {
    std::string msg;
public:

    semantic_error()=default;
    
    semantic_error(const std::string& m);

    /*copy constructor*/
    semantic_error(const semantic_error& other);

    /*copy assignment constructor*/
    semantic_error& operator=(const semantic_error& other);

    /*what is virtual function in std::exception*/
    const char* what() const noexcept override ;
};

class semantic_analyser{
public:
    /* when try to fetching the data from table*/
    void check_table_existence(std::string& table_name);
    /* when try to making the table*/
    void check_table_already_present(std::string& table_name);
    /*when try to get columns data*/
    void check_column_existence(std::string& table_name,std::string& column_name);
    /*whether database present*/
    void check_database_existence(AST* obj);
    /*index present or not while using*/
    void check_index_existence(AST* obj);
    /* check index duplication*/
    void check_index_already_present(AST* obj);
};
extern semantic_analyser semantic_analysis;
#endif