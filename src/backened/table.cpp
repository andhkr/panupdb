#include "include/backened/table.hpp"
#include "include/datatypes.hpp"
#include "iomanip"

table_column::table_column(column_definition* obj){
    column_name = obj->Column;
    type = obj->Type.release();
    constraints = obj->constraints.release();
}

size_t table_column::serialise(char* buffer){
    /*to set the default and nullable*/
    size_t total_obj_size = get_total_sizeof_object(); 

    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        memcpy(buffer+offset,src,size);
        offset += size;
    };

    size_t column_name_len = column_name.size();

    write(&column_name_len,sizeof(column_name_len));
    write(column_name.data(),column_name_len);
    size_t bytes_written = type->serialise(buffer+offset);
    offset += bytes_written;
    write(&nullable,sizeof(nullable));

    write(&has_default,sizeof(bool));
    if(has_default){
        offset += dflt_value->serialise(buffer+offset);
    }

    write(&total_constraints,sizeof(total_constraints));
    column_constraints* curr = constraints;
    while(curr){
        offset += curr->serialise(buffer+offset);
        curr = curr->next_constraint;
    }

    total_obj_size = offset + sizeof(total_object_size);
    write(&total_object_size,sizeof(total_obj_size));

    return offset;
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

    type = get_polymorphic_obj(buffer+offset);

    size_t bytes_written = type->get_total_object_size();
    offset += bytes_written;
    
    read(&nullable,sizeof(nullable));
    read(&has_default,sizeof(bool));

    if(has_default){
        dflt_value = get_polymorphic_obj(buffer+offset);
        offset += dflt_value->get_total_object_size();
    }

    read(&total_constraints,sizeof(uint));
    column_constraints* curr = constraints;
    
    for(uint i = 0;i<total_constraints;++i){
        if(constraints==nullptr){
            constraints = get_polymorphic_constraints(buffer+offset);
            offset += constraints->get_total_sizeof_object();
            curr = constraints;
        }else{
            curr->next_constraint = get_polymorphic_constraints(buffer+offset);
            offset += curr->next_constraint->get_total_sizeof_object();
            curr = curr->next_constraint;
        }
    }

    read(&total_object_size,sizeof(total_object_size));

    return offset;
}

size_t table_column::get_total_sizeof_object(){
    if(total_object_size) return total_object_size;
    size_t total = 0;
    total+= sizeof(total_object_size);
    total+= sizeof(size_t) + column_name.size();
    total+= type->get_total_object_size();
    total+= sizeof(bool);
    total+= sizeof(bool);
    
    column_constraints* curr = constraints;
    while(curr){
        if(constraints->constrt_type()==NOT_NULL){
            nullable = false;
        }
        else if(curr->constrt_type()==DEFAULT_VALUE){
            has_default = true;
            dflt_value = static_cast<default_value*>(curr)->value;
            total+= dflt_value->get_total_object_size();
        }
        total+= constraints->get_total_sizeof_object();
        curr = curr->next_constraint;
        total_constraints++;
    }

    total += sizeof(total_constraints);
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
        }

        std::cout << "\n";
    }
}

id_name::id_name(uint id,std::string name):file_id(id),file_name(name){}

size_t id_name::serialise(char* buffer){
    
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        if(offset>512){
            std::cout<<"slot_serialisation failed"<<
            offset<<" "<<512<<std::endl;
        }
        memcpy(buffer+offset,src,size);
        offset += size;
    };

    write(&file_id,sizeof(file_id));
    size_t len = file_name.size();
    write(&len,sizeof(len));
    write(file_name.data(),len);
    return offset;
}

size_t id_name::deserialise(const char* buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer + offset,size);
        offset += size;
    };

    read(&file_id,sizeof(file_id));
    size_t len = 0;
    read(&len,sizeof(len));
    file_name.resize(len);
    read(&file_name[0],len);
    return offset;
}

size_t id_name::get_total_sizeof_object(){
    return sizeof(file_id) + sizeof(size_t) + file_name.size();
}
