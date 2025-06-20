#ifndef SELECT_LOG_HPP
#define SELECT_LOG_HPP

#include "ast.hpp"
#include <vector>
#include <memory>
#include "backened/table.hpp"
#include <string>

/*logical operation type*/
enum logical_op_type{
    SCAN,
    SELECT,
    JOIN,
    PROJECT,
    TOTLA_TYPE
};

extern std::unordered_map<std::string,std::string> alias_resolver;

struct logical_op{
    
    logical_op()=default;
    logical_op(logical_op_type t);
    virtual ~logical_op()=default;
    logical_op_type type;
    std::vector<std::unique_ptr<logical_op>> children;
};

/*from clause: gives alias, joins and their condition*/
struct scan:logical_op{
    std::string table_name;
    
    scan() = default;
    scan(std::string& tbl);

};

/*condition over which filtering occur*/
struct selection:logical_op{
    std::unique_ptr<condition> predicate;

    selection()=default;
    selection(std::unique_ptr<condition> predicate);
    selection(std::unique_ptr<condition> predicate,std::unique_ptr<logical_op> child);
};
 
struct projection:logical_op{
    /*
    columns
    expression over columns and then renaming
    table : columns according to alias,
    */
   std::vector<AST*> columns_list;

   projection() = default;
   projection(std::unique_ptr<logical_op> child);
   void add_column(AST* clmn);
};

using logical_op_uptr = std::unique_ptr<logical_op>;

logical_op_uptr get_logical_ast(select_node* ast);

#endif