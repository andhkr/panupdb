#include "include/constraints.hpp"
#include "include/backened/table.hpp"

#include "include/query_processor.hpp"

constraint_type primary_key::constrt_type(){
    return PRIMARY_KEY;
}

std::string primary_key::get_constrt_name(){
    return "Primary Key";
}

bool primary_key::validate(datatype* col_val_ptr, table* table,int col_id){
    /*
    primary key:not null and unique
    */

    if(col_val_ptr == nullptr){
        std::cerr<<"Primary Key Constraints Voilated: value can't be NULL"<<std::endl;
        exit(EXIT_FAILURE);
    }

    
    if(catlg_man->validate_uniqueness(col_val_ptr,table,col_id)){
        std::cerr<<"Primary Key Unique Constraints voileted"<<std::endl;
        exit(EXIT_FAILURE);
    }
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

bool not_null::validate(datatype* col_val_ptr, table* table,int col_id){
    if(col_val_ptr == nullptr){
        std::cerr<<"Primary Key Constraints Voilated: value can't be NULL"<<std::endl;
        exit(EXIT_FAILURE);
    }
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

bool default_value::validate(datatype* col_val_ptr, table* table,int col_id){
    /*row.primary key is valid --> true */
    if(col_val_ptr == nullptr){
        col_val_ptr = table->columns[col_id]->dflt_value;
    }
    return true;
}

size_t default_value::serialise(char* buffer){
    constraint_type type = DEFAULT_VALUE;
    memcpy(buffer,&type,sizeof(constraint_type));
    size_t written_bytes = value->serialise(buffer+sizeof(type));
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
