#include "include/select_log.hpp"


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

    AST* curr = ast->table_reference_list.get();
    std::unique_ptr<logical_op> scanobj = std::make_unique<scan>(static_cast<from_clause*>(curr)->first_table->identifier);

    // while(curr){
    //     switch(curr->type){
    //         case tbl:{
    //             if(curr->ptr_children){
    //                 alias_resolver[curr->identifier] = curr->ptr_children->identifier;
    //             }else{
    //                 alias_resolver[curr->identifier] = curr->identifier;
    //             }
    //             static_cast<scan*>(scanobj.get())->table_name = curr->identifier;
    //             std::cout<<curr->identifier<<std::endl;
    //             break;

    //         }
    //         default:{
    //             break;
    //         }
    //     }
    //     curr = curr->ptr_sibling;
    // }

    logical_op_uptr filter   = std::make_unique<selection>(std::move(ast->where_clause),std::move(scanobj));
    logical_op_uptr proj_obj = std::make_unique<projection>(std::move(filter));

    curr = ast->select_list.get();
    while(curr){
        static_cast<projection*>(proj_obj.get())->columns_list.push_back(curr);
        curr = curr->ptr_sibling;
    }
    
    return proj_obj;
}
