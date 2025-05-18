#include "include/datatypes.hpp"

/*----------------------intype---------------------------*/

type inttype::get_type(){
    return INT;
}

std::string inttype::get_typename(){
    return "int";
}

size_t inttype::get_size(){
    return sizeof(int);
}

// for semantic check
bool inttype::is_compatible(datatype& other){
    return other.is_numeric();
}

bool inttype::is_numeric() {return true;}

// for storing in file and reading from file
void inttype::serialise (std::ostream& out){
    /*yet to implemented*/
}
void inttype::deserialise (std::istream& in){
    /*yet to implemented*/
}

// for parser
std::unique_ptr<datatype> inttype::create_int() {
    return std::make_unique<inttype>();
}

/*---------------------------varchar--------------------------*/

explicit varchar::varchar(size_t len) : maxlength(len) {}

type varchar::get_type(){
    return VARCHAR;
}

std::string varchar::get_typename(){
    return "varchar(" + std::to_string(maxlength) + ")";
}

size_t varchar::get_size(){
    return maxlength;
}

// for semantic check
bool varchar::is_compatible(datatype& other){
    return other.is_text();
}

bool varchar::is_text() {return true;}

// for storing in file and reading from file
void varchar::serialise (std::ostream& out){
    /*yet to implemented*/
}
void varchar::deserialise (std::istream& in){
    /*yet to implemented*/
}   

// for parser

std::unique_ptr<datatype> varchar::create_varchar(size_t maxlen){
    return std::make_unique<varchar>(maxlen);
}
