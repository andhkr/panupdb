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
    return sizeof(type) + sizeof(int);
}

size_t inttype::deserialise (const char* buffer){
    memcpy(&value,buffer+sizeof(type),sizeof(int));
    return sizeof(int);
}

size_t inttype::get_total_object_size(){
    return sizeof(type) + sizeof(int);
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
    size_t offset = 0;
    memcpy(buffer+offset,&type_id,sizeof(type));
    offset += sizeof(type);
    memcpy(buffer+offset,&maxlength,sizeof(maxlength));
    offset += sizeof(maxlength);
    size_t size = value.size();
    memcpy(buffer+offset,&size,sizeof(size));
    offset+= sizeof(size);

    memcpy(buffer+offset,value.data(),size);
    offset += size;
    return offset;
}
size_t varchar::deserialise (const char* buffer){
    size_t size = 0;
    size_t offset = sizeof(type);
    memcpy(&maxlength,buffer+offset,sizeof(size_t));
    offset += sizeof(size_t);
    memcpy(&size,buffer+offset,sizeof(size));
    offset += sizeof(size);
    value.resize(size);
    memcpy(&value[0],buffer+offset,size);
    offset += size;
    return offset;
}   

size_t varchar::get_total_object_size(){
    size_t total = sizeof(type) + 2*sizeof(size_t) + value.size();
    return total;
}

// for parser

std::unique_ptr<datatype> varchar::create_varchar(size_t maxlen){
    return std::make_unique<varchar>(maxlen);
}

/*datafactory function*/
datatype* get_polymorphic_obj(const char* buffer){
    type type_id;
    memcpy(&type_id,buffer,sizeof(type));
    datatype* poly_obj;
    switch(type_id){
        case INT:{
            poly_obj = new inttype;
            break;
        }case VARCHAR:{
            poly_obj = new varchar;
            break;
        }default:{
            break;
        }
    }
    poly_obj->deserialise(buffer);
    return poly_obj;
}
