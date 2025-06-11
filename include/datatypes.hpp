#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <iostream>
#include <string>
#include <memory>
#include <variant>
#include <cstring>

/*creating a abstract class for different dataypes handling*/

enum type {
    INT,
    VARCHAR,
    CHAR,
    NUMERIC,
    DATE,
    TEXT
};

class datatype{
public:

    virtual ~datatype() = default;

    virtual type get_type() = 0;

    virtual std::string get_typename() = 0;

    virtual size_t get_size() = 0;

    // for semantic check
    virtual bool is_compatible(datatype& other) = 0;
    virtual bool is_numeric(){ return false;}
    virtual bool is_text(){return false;}

    // for storing in file and reading from file
    virtual size_t serialise (char* buffer) = 0;
    virtual size_t deserialise (const char* buffer) = 0;

    virtual size_t get_total_object_size()=0;
};

class inttype : public datatype {
public:
    type get_type();
    int value=0;
    std::string get_typename();

    size_t get_size();

    // for semantic check
    bool is_compatible(datatype& other);

    bool is_numeric();

    // for storing in file and reading from file
    size_t serialise (char* buffer);
    size_t deserialise (const char* buffer);

    size_t get_total_object_size();

    // for parser
    static std::unique_ptr<datatype> create_int();
};

class varchar : public datatype {
private:
    size_t maxlength = 0;
public:

    std::string value{};

    varchar()=default;
    explicit varchar(size_t len);
    
    type get_type();

    std::string get_typename();

    size_t get_size();

    // for semantic check
    bool is_compatible(datatype& other);

    bool is_text();

    // for storing in file and reading from file
    size_t serialise (char* buffer);
    size_t deserialise (const char* buffer);   
    
    size_t get_total_object_size();
    // for parser

    static std::unique_ptr<datatype> create_varchar(size_t maxlen);
};


datatype* get_polymorphic_obj(const char* buffer);


#endif
