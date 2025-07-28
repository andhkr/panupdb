#ifndef AST_HPP
#define AST_HPP

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include "datatypes.hpp"
#include "constraints.hpp"

extern std::string database_path;

enum nodetype{
    bop,/*binary operator*/
    val,
    tbl_or_col,
    tbl,
    TUPLE,
    TOTAL
};

struct AST{
    std::string identifier; /*select,insert,table_name,column_list,column_name*/
    AST* ptr_children=nullptr;
    AST* ptr_sibling=nullptr;
    nodetype type;

    AST()=default;
    AST(std::string id_name);
    AST(std::string,nodetype);
    AST(nodetype);
    // // AST(std::string id_name,AST* ptr_children);
    // AST(std::string id_name,AST* ptr_children,AST* ptr_sibling);
    // // AST(std::string id_name,AST* ptr_sibling);
    virtual ~AST()=default;
    virtual void print_ast(int identation);
};

/*condition can be where clause or join condition*/
struct condition {
    virtual ~condition()=default;
    virtual bool evaluate(std::vector<datatype*>& tuple,table* tbl)=0;
    virtual void print(int)=0;
};

struct And_cond :public condition{
    condition* L;
    condition* R;
    And_cond()=default;
    And_cond(condition*,condition*);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
    void print(int);
};

struct Or_cond :public condition{
    condition* L;
    condition* R;
    Or_cond()=default;
    Or_cond(condition*,condition*);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
    void print(int);
};


struct comparison : condition{
    AST* leftexpr;
    AST* rightexpr;
    Ops op;
    
    comparison()=default;
    comparison(AST*,AST*,Ops);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
    void print(int);
};

struct from_clause:public AST{
    // phase 1: table name without joins and aliases
    std::unique_ptr<AST> first_table;
};

struct select_node:public AST{
    // phase 1: select * / columns from a table
    std::unique_ptr<AST> select_list = nullptr;
    std::unique_ptr<from_clause> table_reference_list = nullptr;
    std::unique_ptr<condition> where_clause = nullptr;
    void print_ast(int) override;
};

struct column_definition:public AST{
    std::string Column;
    std::unique_ptr<datatype> Type;
    std::unique_ptr<column_constraints> constraints;

    void print_ast (int identation) override;
};

struct create_table:public AST{
    /*phase 1:*/
    std::unique_ptr<AST> table_name;
    column_definition* columns_definitions;
    /*phase 2:*/
    std::unique_ptr<AST> explicit_constraints_on_table;

    void print_ast(int) override;
};

struct insert_stmt:public AST{
    std::unique_ptr<AST> table_name;
    AST* columns_to_insert;
    AST* values;

    void print_ast(int) override;
};

struct update : public AST{
    std::unique_ptr<AST> table_name;
    AST* update_list;
    std::unique_ptr<condition> where_clause = nullptr;
    void print_ast(int) override;
};

struct Delete : public AST{
    std::unique_ptr<AST> table_name;
    std::unique_ptr<condition> where_clause = nullptr;
    void print_ast(int) override;
};

struct create_database: AST{
    std::string database_name;
    create_database(std::string name);
    void print_ast(int);
    void createdb();
};

struct drop_database: AST{
    std::string database_name;
    drop_database(std::string name);
    void print_ast(int);
    void dropdb();
};

#endif