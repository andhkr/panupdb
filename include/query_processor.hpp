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

/*condition can be where clause or join condition*/
struct condition {
    virtual ~condition()=default;
    virtual bool evaluate(std::vector<datatype*>& tuple,table* tbl)=0;
};

struct And_cond :public condition{
    condition* L;
    condition* R;
    And_cond()=default;
    And_cond(condition*,condition*);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
};

struct Or_cond :public condition{
    condition* L;
    condition* R;
    Or_cond()=default;
    Or_cond(condition*,condition*);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
};


struct comparison : condition{
    AST* leftexpr;
    AST* rightexpr;
    Ops op;
    
    comparison()=default;
    comparison(AST*,AST*,Ops);
    bool evaluate(std::vector<datatype*>& tuple,table* tbl);
};

extern query_processor query_executor;
extern catalog_manager* catlg_man;
#endif