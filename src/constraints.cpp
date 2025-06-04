#include "include/constraints.hpp"

constraint_type primary_key::constrt_type(){
    return PRIMARY_KEY;
}

std::string primary_key::get_constrt_name(){
    return "Primary Key";
}

bool primary_key::validate(const void* row,const void* column){
    /*row.primary key is valid --> true */
    return true;
}

size_t primary_key::serialise(char* buffer){
    constraint_type type = PRIMARY_KEY;
    memcpy(buffer,&type,sizeof(constraint_type));
    return sizeof(type);
}

size_t primary_key::deserialise(const char* buffer){
    constraint_type type;
    memcpy(&type,buffer,sizeof(type));
    return sizeof(type);
}

size_t primary_key::get_total_sizeof_object(){
    return sizeof(type);
}

constraint_type not_null::constrt_type(){
    return NOT_NULL;
}

std::string not_null::get_constrt_name(){
    return "NOT NULL";
}

bool not_null::validate(const void* row,const void* column){
    /*row.primary key is valid --> true */
    return true;
}

size_t not_null::serialise(char* buffer){
    constraint_type type = NOT_NULL;
    memcpy(buffer,&type,sizeof(constraint_type));
    return sizeof(type);
}

size_t not_null::deserialise(const char* buffer){
    constraint_type type;
    memcpy(&type,buffer,sizeof(type));
    return sizeof(type);
}

size_t not_null::get_total_sizeof_object(){
    return sizeof(type);
}

default_value::default_value(datatype* value):value(value){}

constraint_type default_value::constrt_type(){
    return DEFAULT_VALUE;
}

std::string default_value::get_constrt_name(){
    return "default";
}

bool default_value::validate(const void* row,const void* column){
    /*row.primary key is valid --> true */
    return true;
}

size_t default_value::serialise(char* buffer){
    constraint_type type = DEFAULT_VALUE;
    memcpy(buffer,&type,sizeof(constraint_type));
    size_t written_bytes = value->serialise(buffer+sizeof(type));
    std::cout<<"default "<<written_bytes<<std::endl;
    return written_bytes+sizeof(type);
}

size_t default_value::deserialise(const char* buffer){
    value = get_polymorphic_obj(buffer+sizeof(constraint_type));
    return value->get_total_object_size();
}

size_t default_value::get_total_sizeof_object(){
    return sizeof(type)+value->get_total_object_size();
}

column_constraints* get_polymorphic_constraints(const char* buffer){
    constraint_type type;
    memcpy(&type,buffer,sizeof(type));
    column_constraints* poly_obj = nullptr;
    switch(type){
        case PRIMARY_KEY:{
            poly_obj = new primary_key;
            break;
        }
        case NOT_NULL:{
            poly_obj = new not_null;
            break;
        }
        case DEFAULT_VALUE:{
            poly_obj = new default_value;
            break;
        }default:{
            break;
        }
    }
    poly_obj->deserialise(buffer);
    return poly_obj;
}
