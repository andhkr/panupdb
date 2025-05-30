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
size_t inttype::serialise (char* buffer){
    type type_id = INT;
    memcpy(buffer,&type_id,sizeof(type));
    memcpy(buffer+sizeof(type),&value,sizeof(value));
    return sizeof(type) + sizeof(value);
}

size_t inttype::deserialise (const char* buffer){
    memcpy(&value,buffer+sizeof(type),sizeof(value));
    return sizeof(value);
}

size_t inttype::get_total_object_size(){
    return sizeof(size_t) + sizeof(value);
}
// for parser
std::unique_ptr<datatype> inttype::create_int() {
    return std::make_unique<inttype>();
}

/*---------------------------varchar--------------------------*/

varchar::varchar(size_t len) : maxlength(len) {}

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
size_t varchar::serialise (char* buffer){
    type type_id = VARCHAR;
    memcpy(buffer,&type_id,sizeof(type));
    memcpy(buffer+sizeof(type),&value,sizeof(value));
    return sizeof(type) + sizeof(value);
}
size_t varchar::deserialise (const char* buffer){
    memcpy(&value,buffer+sizeof(type),sizeof(value));
    return sizeof(value);
}   

size_t varchar::get_total_object_size(){
    return sizeof(size_t) + sizeof(value);
}
// for parser

std::unique_ptr<datatype> varchar::create_varchar(size_t maxlen){
    return std::make_unique<varchar>(maxlen);
}

/*datafactory function*/
std::unique_ptr<datatype> get_polymorphic_obj(char* buffer){
    type type_id;
    memcpy(&type_id,buffer,sizeof(type));
    std::unique_ptr<datatype> poly_obj;
    switch(type_id){
        case INT:{
            poly_obj = std::make_unique<inttype>();
            break;
        }case VARCHAR:{
            poly_obj = std::make_unique<varchar>();
            break;
        }default:{
            break;
        }
    }
    poly_obj->deserialise(buffer);
    return poly_obj;
}
