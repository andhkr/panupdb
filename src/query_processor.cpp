#include "include/ast.hpp"
#include "include/constraints.hpp"

struct table_specific_constraints{

};

struct table_column{
    std::string column_name;
    datatype* type;
    bool nullable=true;
    datatype* dflt_value;
    column_constraints* constraints;
    size_t total_object_size = 0;

    table_column()=default;

    table_column(column_definition* obj){
        column_name = obj->Column;
        type = obj->Type.release();
        constraints = obj->constraints.release();
    }

    size_t serialise(char* buffer){
        size_t total_obj_size = get_total_sizeof_object();
        auto write = [&](void* src,size_t size){
            memcpy(buffer,src,size);
            buffer += size;
        };

        size_t column_name_len = column_name.size();

        write(&column_name_len,sizeof(column_name_len));
        write(column_name.data(),column_name_len);
        size_t bytes_written = type->serialise(buffer);
        buffer += bytes_written;
        write(&nullable,sizeof(nullable));
        buffer += dflt_value->serialise(buffer);

        column_constraints* curr = constraints;
        while(curr){
            buffer+= constraints->serialise(buffer);
            curr = curr->next_constraint;
        }

        write(&total_object_size,sizeof(total_obj_size));

        return get_total_sizeof_object();
    }

    size_t deserialise(const char* buffer){
        size_t offset = 0;

        auto read = [&](void* dest,size_t size){
            memcpy(dest,buffer+offset,size);
            offset += size;
        };

        size_t column_name_len = 0;

        read(&column_name_len,sizeof(column_name_len));
        column_name.resize(column_name_len);
        read(&column_name[0],column_name_len);
        size_t bytes_written = type->deserialise(buffer+offset);
        offset += bytes_written;
        read(&nullable,sizeof(nullable));
        offset += dflt_value->deserialise(buffer+offset);

        column_constraints* curr = constraints;
        while(curr){
            offset+= constraints->deserialise(buffer+offset);
            curr = curr->next_constraint;
        }

        read(&total_object_size,sizeof(total_object_size));
        return get_total_sizeof_object();
    }

    size_t get_total_sizeof_object(){
        if(total_object_size) return total_object_size;
        size_t total = 0;
        total+= sizeof(total_object_size);
        total+= sizeof(size_t) + column_name.size();
        total+= type->get_total_object_size();
        total+= sizeof(nullable);
        total+= dflt_value->get_total_object_size();
        column_constraints* curr = constraints;
        while(curr){
            if(constraints->constrt_type()==NOT_NULL){
                nullable = false;
            }
            else if(curr->constrt_type()==DEFAULT_VALUE){
                dflt_value = static_cast<default_value*>(curr)->value;
            }
            total+= constraints->get_total_sizeof_object();
            curr = curr->next_constraint;
        }
        return total_object_size = total;
    }


};

struct table{
    std::string table_name;
    std::vector<table_column*> columns;
    std::vector<table_specific_constraints*> on_table_constraints;
    /*used by query planar*/
    std::vector<std::vector<std::string>> columns_have_index;
    uint column_cts;
};

struct query_processor{
  
    query_processor()=default;

    static table* process_create_table(create_table* obj){
        table* tbl = new table;
        tbl->table_name = std::move(obj->table_name->identifier);
        std::vector<table_column*> columns;
        uint ct = 0;
        column_definition* curr = obj->columns_definitions;
        while(curr){
            table_column* col = new table_column(curr);
            columns.push_back(col);
            ct++;
            curr = (column_definition*)(((AST*)curr)->ptr_sibling);
        }
        tbl->columns = columns;
        tbl->column_cts = ct;

        return tbl;
    }
};