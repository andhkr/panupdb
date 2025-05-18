#ifndef AST_HPP
#define AST_HPP

#include<iostream>
#include<string>

struct AST{
    std::string  id_name; /*select,insert,table_name,column_list,column_name*/
    AST* ptr_children=nullptr;
    AST* ptr_sibling=nullptr;

    AST(std::string id_name);
    // AST(std::string id_name,AST* ptr_children);
    AST(std::string id_name,AST* ptr_children,AST* ptr_sibling);
    // AST(std::string id_name,AST* ptr_sibling);

    ~AST();

    void print_ast(){/*yet to implemented*/}
};

#endif