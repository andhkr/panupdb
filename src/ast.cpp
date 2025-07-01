#include "include/ast.hpp"
#include <cstring>
#include "include/evaluate_comp_expr.hpp"
#include "include/backened/table.hpp"

And_cond::And_cond(condition* Lexpr, condition* Rexpr):L(Lexpr),R(Rexpr){}

bool And_cond::evaluate(std::vector<datatype*>& tuple,table* tbl){
    return L->evaluate(tuple,tbl) && R->evaluate(tuple,tbl);
}

void And_cond::print(int iden){
    int level = iden;
    while(level--){
        std::cout<<" ";
    }
    std::cout<<"|-AND"<<std::endl;
    L->print(iden+1);
    R->print(iden+1);
}

Or_cond::Or_cond(condition* Lexpr, condition* Rexpr):L(Lexpr),R(Rexpr){}

bool Or_cond::evaluate(std::vector<datatype*>& tuple,table* tbl){
    return L->evaluate(tuple,tbl) || R->evaluate(tuple,tbl);
}

void Or_cond::print(int iden){
    int level = iden;
    while(level--){
        std::cout<<" ";
    }
    std::cout<<"|-Or"<<std::endl;
    L->print(iden+1);
    R->print(iden+1);
}

comparison::comparison(AST* L,AST* R,Ops Op):leftexpr(L),rightexpr(R),op(Op){}

datatype* evaluate_expr(AST* expr,std::vector<datatype*>& tuple,table* tbl);

void comparison::print(int iden){
    int level = iden;
    while(level--){
        std::cout<<" ";
    }
    switch (op)
    {
    case Ops::EQ:{
        std::cout<<"|-[=]"<<std::endl;
        break;
    }
    case Ops::LT:{
        std::cout<<"|-[<]"<<std::endl;
        break;
    }
    case Ops::GT:{
        std::cout<<"|-[>]"<<std::endl;
        break;
    }
    default:
        break;
    }

    leftexpr->print_ast(iden+1);
    rightexpr->print_ast(iden+1);
}

bool comparison::evaluate(std::vector<datatype*>& tuple,table* tbl){
    
    return evaluate_and_comp(evaluate_expr(leftexpr,tuple,tbl), evaluate_expr(rightexpr,tuple,tbl),op);
}

datatype* evaluate_expr(AST* expr,std::vector<datatype*>& tuple,table* tbl){

   switch(expr->type){
    case bop:{
        break;
    }
    case val:{
        return reinterpret_cast<datatype*>(expr->ptr_children);

    }case tbl_or_col:{
        return tuple[tbl->index_of_col(expr->identifier)];

    }default:{
        break;
    }
   }
   return nullptr;

}

AST::AST(std::string id_name):identifier(id_name){}

// // AST::AST(std::string id_name,AST* ptr_children):id_name(id_name),ptr_children(ptr_children){}

// AST::AST(std::string id_name,AST* ptr_children,AST* ptr_sibling):id_name(id_name),ptr_children(ptr_children),ptr_sibling(ptr_sibling){}

// // AST::AST(std::string id_name,AST* ptr_sibling):id_name(id_name),ptr_sibling(ptr_sibling){}

AST::AST(std::string id_name,nodetype N_type):identifier(id_name),type(N_type){}
AST::AST(nodetype N_type):type(N_type){}

AST::~AST(){
    delete this->ptr_sibling;
    delete this->ptr_children;
}

void AST::print_ast(int identation){
    int iden = identation;
    while(iden--){
        std::cout<<" ";
    }
    switch(type){
        case nodetype::tbl_or_col:{
            std::cout<<"|- "<<this->identifier<<std::endl;
            if(this->ptr_children)
                this->ptr_children->print_ast(identation+1);
            if(this->ptr_sibling){
                if(this->identifier != "DEFAULT")
                this->ptr_sibling->print_ast(identation);
                else {
                    iden = identation;
                    while(iden--){
                        std::cout<<" ";
                    }
                    switch(((datatype*)(this->ptr_sibling))->get_type()){
                        case INT:{
                            std::cout<<"  |- "<<(((inttype*)(this->ptr_sibling))->value)<<std::endl;
                            break;
                        }
                        case VARCHAR:{
                            std::cout<<"  |- "<<(((varchar*)(this->ptr_sibling))->value)<<std::endl;
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }
            }
            break;
        }case nodetype::val :{
            
            datatype* data = reinterpret_cast<datatype*>(this->ptr_children);
            switch (data->get_type())
            {
            case INT:{
                std::cout<<"|- "<<static_cast<inttype*>(data)->value<<std::endl;
                break;
            }
            case VARCHAR:{
                std::cout<<"|- "<<static_cast<varchar*>(data)->value<<std::endl;
                break;
            }
            default:
                break;
            }
        }default:{
            break;
        }
    }
    
}

void select_node::print_select(){
    std::cout<<"SELECT STATEMENT"<<std::endl;
    std::cout<<" columns in select list"<<std::endl;
    this->select_list->print_ast(2);
    std::cout<<"from_clause"<<std::endl;
    this->table_reference_list->first_table->print_ast(2);
    if(where_clause){
        std::cout<<"where_clause"<<std::endl;
        where_clause->print(2);
    }


}

void create_identention(int iden){
    while(iden--){
        std::cout<<" ";
    }
}

void column_definition::print_column_def(int identation){
    create_identention(identation);
    std::cout<<"Column Name"<<std::endl;
    create_identention(identation+1);
    std::cout<<"|- "<<this->Column<<std::endl;
    create_identention(identation);
    std::cout<<"Type"<<std::endl;
    create_identention(identation+1);
    std::cout<<"|- "<<this->Type->get_typename()<<std::endl;
    create_identention(identation);
    std::cout<<"constraints"<<std::endl;
    // if(this->constraints){
    //     this->constraints->print_ast(identation+1);
    // }

}

void create_table::print_table(){
    std::cout<<"CREATE TABLE"<<std::endl;
    std::cout<<" table name"<<std::endl;
    this->table_name->print_ast(2);
    column_definition* curr = this->columns_definitions;
    while(curr){
        curr->print_column_def(1);
        curr = (column_definition*)(((AST*)curr)->ptr_sibling);
    }
}

void insert_stmt::print_insert(){
    std::cout<<"INSERT INTO TABLE "<<this->table_name->identifier<<std::endl;
    std::cout<<"columns list"<<std::endl;
    if(this->columns_to_insert){
        this->columns_to_insert->print_ast(1);
    }
    std::cout<<"VALUES"<<std::endl;
    AST* tuples = this->values;
    while(tuples){
        AST* curr = tuples->ptr_children;
        while(curr){
            switch(((datatype*)(curr->ptr_children))->get_type()){
                case INT:{
                    std::cout<<"  |- "<<(((inttype*)(curr->ptr_children))->value)<<std::endl;
                    break;
                }
                case VARCHAR:{
                    std::cout<<"  |- "<<(((varchar*)(curr->ptr_children))->value)<<std::endl;
                    break;
                }
                default:{
                    break;
                }
            }
            curr = curr->ptr_sibling;
        }
        tuples = tuples->ptr_sibling;
    }
}


void update::print_update(){
    std::cout<<"UPDATE"<<std::endl;
    std::cout<<table_name->identifier<<std::endl;
    AST* curr = update_list;
    while(curr){
        curr->print_ast(0);
        curr = curr->ptr_sibling;
    }
    where_clause->print(0);
}

void Delete::print_delete(){
    std::cout<<"DELETE"<<std::endl;
    std::cout<<table_name->identifier<<std::endl;
    where_clause->print(0);
}
