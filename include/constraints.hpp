#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include <iostream>
#include <cstring>
#include "datatypes.hpp"

struct table;

enum constraint_type {
    PRIMARY_KEY,
    UNIQUE,
    NOT_NULL,
    DEFAULT_VALUE
};

struct column_constraints{

    column_constraints* next_constraint = nullptr;

    virtual ~column_constraints() = default;

    virtual constraint_type constrt_type() = 0;

    virtual std::string get_constrt_name() = 0;

    virtual bool validate(datatype* row, table* table,int col_id) = 0;

    virtual size_t serialise(char* buffer) = 0;

    virtual size_t deserialise(const char* buffer) = 0;

    virtual size_t get_total_sizeof_object()=0;

    virtual void print_constraints(int)=0;

};

struct primary_key : public column_constraints{

    constraint_type constrt_type();

    std::string get_constrt_name();

    bool validate(datatype* row, table* table,int col_id);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_sizeof_object();

    void print_constraints(int) override;
};

// struct unique : public column_constraints{

//     constraint_type constrt_type();

//     std::string get_constrt_name();

//     bool validate(datatype* row, table* table,int col_id);

//     size_t serialise(char* buffer);

//     constraint_type deserialise(const char* buffer);
// size_t get_total_sizeof_object();
// };

struct not_null : public column_constraints {

    constraint_type constrt_type();

    std::string get_constrt_name();

    bool validate(datatype* row, table* table,int col_id);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_sizeof_object();

    void print_constraints(int) override;
};

struct default_value : public column_constraints {

    datatype* value;

    default_value()=default;
    default_value(datatype*);

    ~default_value();

    constraint_type constrt_type();

    std::string get_constrt_name();

    bool validate(datatype* row, table* table,int col_id);

    size_t serialise(char* buffer);

    size_t deserialise(const char* buffer);

    size_t get_total_sizeof_object();

    void print_constraints(int) override;
};

column_constraints* get_polymorphic_constraints(const char* buffer);
struct table_specific_constraints{

};

#endif