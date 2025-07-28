#include "include/ast.hpp"
#include <cstring>
#include "include/evaluate_comp_expr.hpp"
#include "include/backened/table.hpp"
#include <filesystem>

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

// And_cond::~And_cond(){
//     delete L;
//     delete R;
// }


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

// Or_cond::~Or_cond(){
//     delete L;
//     delete R;
// }



comparison::comparison(AST* L,AST* R,Ops Op):leftexpr(L),rightexpr(R),op(Op){}

// comparison::~comparison(){
//     delete leftexpr;
//     delete rightexpr;
// }

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

// AST::~AST(){
//     if(this->ptr_sibling)
//         // delete this->ptr_sibling;
//     if(this->ptr_children)
//         // delete this->ptr_children;
// }

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

// from_clause::~from_clause(){
//     // if(first_table)
//     // delete first_table;
// }

void select_node::print_ast(int identation){
    std::cout<<"SELECT STATEMENT"<<std::endl;
    std::cout<<" columns in select list"<<std::endl;
    this->select_list->print_ast(identation+1);
    std::cout<<"from_clause"<<std::endl;
    this->table_reference_list->first_table->print_ast(identation+1);
    if(where_clause){
        std::cout<<"where_clause"<<std::endl;
        where_clause->print(identation+1);
    }
}


// select_node::~select_node(){
//     // if(select_list)
//     // delete select_list;
//     // if(table_reference_list)
//     // delete table_reference_list;
//     // if(where_clause)
//     // delete where_clause;

// }

void create_identention(int iden){
    while(iden--){
        std::cout<<" ";
    }
}

// column_definition::~column_definition(){
//     // delete Type;
//     // column_constraints* curr = constraints;
//     // while(curr){
//     //     column_constraints* next = curr->next_constraint;
//     //     delete curr;
//     //     curr = next;
//     // }
// }

void column_definition::print_ast(int identation){
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
    if(this->constraints){
        this->constraints->print_constraints(identation+1);
    }
}

void create_table::print_ast(int indent=0){
    std::cout<<"CREATE TABLE"<<std::endl;
    std::cout<<" table name"<<std::endl;
    this->table_name->print_ast(2);
    column_definition* curr = this->columns_definitions;
    while(curr){
        curr->print_ast(2);
        curr = (column_definition*)(((AST*)curr)->ptr_sibling);
    }
}

// create_table::~create_table(){
//     // delete table_name;
//     // delete columns_definitions;
//     // if(explicit_constraints_on_table)
//     // delete explicit_constraints_on_table;
// }

void insert_stmt::print_ast(int indent=0){
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

// insert_stmt::~insert_stmt(){
//     // if(table_name) delete table_name;
//     // if(columns_to_insert) delete columns_to_insert;
//     // if(values) delete values;
// }

void update::print_ast(int indent=0){
    std::cout<<"UPDATE"<<std::endl;
    std::cout<<table_name->identifier<<std::endl;
    AST* curr = update_list;
    while(curr){
        curr->print_ast(indent+1);
        curr = curr->ptr_sibling;
    }
    where_clause->print(indent);
}

// update::~update(){
//     // delete table_name;
//     // delete update_list;
//     // if(where_clause) delete where_clause;
// }

void Delete::print_ast(int indent=0){
    std::cout<<"DELETE"<<std::endl;
    std::cout<<table_name->identifier<<std::endl;
    where_clause->print(indent);
}

// Delete::~Delete(){
//     // delete table_name;
//     // if(where_clause) delete where_clause;
// }

#include <unordered_set>
extern std::unordered_set<std::string> databases_created;
extern std::string current_database;
extern bool connected_to_a_database;

create_database::create_database(std::string name):database_name(name){}

void create_database::print_ast(int indent){
    if(databases_created.find(database_name)!=databases_created.end()){
        std::cerr<<"Database already Exists\n";
        return;
    }
    std::cout<<"CREATE"<<
    " DATABASE"<<
    " |- "<<database_name<<std::endl;
    createdb();
    databases_created.insert(database_name);
}

extern std::string database_root;

void create_database::createdb(){
    std::string dbpath = database_root + "/" + database_name;

     /*create a directory of name database_name in database_root directory */
    std::filesystem::create_directory(dbpath);

    /*then in that directory create folders datafile,index file,catalog file,fsmfiles*/
    std::filesystem::create_directory(dbpath + "/datafile");
    std::filesystem::create_directory(dbpath + "/indexfile");
    std::filesystem::create_directory(dbpath + "/catalog");
    std::filesystem::create_directory(dbpath + "/fsmfile");
}

drop_database::drop_database(std::string name):database_name(name){}

void drop_database::print_ast(int indent){
    if(databases_created.find(database_name)==databases_created.end()){
        std::cerr<<"Database Does Not Exists\n";
        return;
    }
    if(connected_to_a_database && database_name == current_database ){
        std::cerr<<"ERROR:  cannot drop the currently open database"<<std::endl;
        return;
    }
    std::cout<<"DROP"<<
    " DATABASE"<<
    " |- "<<database_name<<std::endl;
    dropdb();
    databases_created.erase(database_name);
}

void drop_database::dropdb(){
    if(!std::filesystem::remove_all(database_root+"/"+database_name)){
        std::cerr<<"Unable to delete database please try again"<<std::endl;
    }
}
