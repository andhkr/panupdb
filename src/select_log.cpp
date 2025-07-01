#include "include/select_log.hpp"
#include "include/semantic.hpp"

std::unordered_map<std::string,std::string> alias_resolver;


logical_op::logical_op(logical_op_type t) : type(t) {}

/*from clause: gives alias, joins and their condition*/
scan::scan(std::string& tbl):logical_op(SCAN),table_name(tbl){}

/*condition over which filtering occur*/

selection::selection(std::unique_ptr<condition> pred):logical_op(SELECT),
predicate(std::move(pred)){}
selection::selection(std::unique_ptr<condition> pred,std::unique_ptr<logical_op> child):logical_op(SELECT),
predicate(std::move(pred)){
    children.push_back(std::move(child));
}


projection::projection(std::unique_ptr<logical_op> child):logical_op(PROJECT){
    children.push_back(std::move(child));
}

void projection::add_column(AST* clmn){
    columns_list.push_back(clmn);
}

logical_op_uptr get_logical_ast(select_node* ast){
    try{
        AST* curr = ast->table_reference_list.get();

        std::string table_name = static_cast<from_clause*>(curr)->first_table->identifier;

        /*currently only one table*/
        semantic_analysis.check_table_existence(table_name);

        std::unique_ptr<logical_op> scanobj = std::make_unique<scan>(table_name);

        logical_op_uptr filter   = std::make_unique<selection>(std::move(ast->where_clause),std::move(scanobj));
        logical_op_uptr proj_obj = std::make_unique<projection>(std::move(filter));
        
        
        curr = ast->select_list.get();
        while(curr){
            static_cast<projection*>(proj_obj.get())->columns_list.push_back(curr);
            semantic_analysis.check_column_existence(table_name,curr->identifier);
            curr = curr->ptr_sibling;
        }
        
        return proj_obj;
    }catch (const semantic_error& e){
        throw e;
    }
}
