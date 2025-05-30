#include "include/backened/table.hpp"
#include "include/datatypes.hpp"
#include "iomanip"

table_column::table_column(column_definition* obj){
    column_name = obj->Column;
    type = obj->Type.release();
    constraints = obj->constraints.release();
}

size_t table_column::serialise(char* buffer){
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

size_t table_column::deserialise(const char* buffer){
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

size_t table_column::get_total_sizeof_object(){
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
#include <iomanip>  // for std::setw

void table::print() {
    const int width_name = 20;
    const int width_type = 15;
    const int width_nullable = 12;
    const int width_default = 20;

    std::cout << "\nTable: " << table_name << "\n\n";

    // Header
    std::cout << std::left
              << std::setw(width_name) << "Column Name"
              << std::setw(width_type) << "Type"
              << std::setw(width_nullable) << "Nullable"
              << std::setw(width_default) << "Default"
              << "\n";

    std::cout << std::string(width_name + width_type + width_nullable + width_default, '-') << "\n";

    // Data rows
    for (auto& col : columns) {
        std::cout << std::left
                  << std::setw(width_name) << col->column_name
                  << std::setw(width_type) << col->type->get_typename()
                  << std::setw(width_nullable) << (col->nullable ? "YES" : "NO");

        if (col->dflt_value) {
            switch (col->dflt_value->get_type()) {
                case INT:
                    std::cout << std::setw(width_default)
                              << std::to_string(static_cast<inttype*>(col->dflt_value)->value);
                    break;
                case VARCHAR:
                    std::cout << std::setw(width_default)
                              << static_cast<varchar*>(col->dflt_value)->value;
                    break;
                default:
                    std::cout << std::setw(width_default) << "UNKNOWN";
                    break;
            }
        } else {
            std::cout << std::setw(width_default) << "NULL";
        }

        std::cout << "\n";
    }
}
