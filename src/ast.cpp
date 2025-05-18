#include "include/ast.hpp"

AST::AST(std::string id_name):id_name(id_name){}

// AST::AST(std::string id_name,AST* ptr_children):id_name(id_name),ptr_children(ptr_children){}

AST::AST(std::string id_name,AST* ptr_children,AST* ptr_sibling):id_name(id_name),ptr_children(ptr_children),ptr_sibling(ptr_sibling){}

// AST::AST(std::string id_name,AST* ptr_sibling):id_name(id_name),ptr_sibling(ptr_sibling){}

AST::~AST(){
    delete this->ptr_sibling;
    delete this->ptr_children;
}
void AST::print_ast(){/*yet to implemented*/}