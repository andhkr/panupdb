#include "include/evaluate_comp_expr.hpp"
/*first i am implimenting comparing evaluated expr*/

/********************************equal[=] operator implementation*********************************/
bool equate_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value == static_cast<inttype*>(right)->value;
}

bool equate_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value == static_cast<varchar*>(right)->value;
}

bool equate_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value == std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func eq_table[TYPE_COUNT][TYPE_COUNT] = {};

bool equate(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func eq_func = eq_table[lhs][rhs];

    if(!eq_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return eq_func(left,right);
}

void init_eq_table(){
    eq_table[type::INT][type::INT] = equate_int;
    eq_table[type::VARCHAR][type::VARCHAR] = equate_varchar;
    eq_table[type::INT][type::VARCHAR] = equate_int_varchar;
    eq_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return equate_int_varchar(r,l); // reverse args
    };
}

/*******************************************lessthan[<] operator *******************************************/

bool lessthan_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value < static_cast<inttype*>(right)->value;
}

bool lessthan_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value < static_cast<varchar*>(right)->value;
}

bool lessthan_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value < std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func lessthan_table[TYPE_COUNT][TYPE_COUNT] = {};

bool lessthan(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func lessthan_func = lessthan_table[lhs][rhs];

    if(!lessthan_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return lessthan_func(left,right);
}

void init_lessthan_table(){
    lessthan_table[type::INT][type::INT] = lessthan_int;
    lessthan_table[type::VARCHAR][type::VARCHAR] = lessthan_varchar;
    lessthan_table[type::INT][type::VARCHAR] = lessthan_int_varchar;
    lessthan_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return lessthan_int_varchar(r,l); // reverse args
    };
}

/****************************************greater than [>] opearator implementation ************************/
bool greaterthan_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value > static_cast<inttype*>(right)->value;
}

bool greaterthan_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value > static_cast<varchar*>(right)->value;
}

bool greaterthan_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value > std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func greaterthan_table[TYPE_COUNT][TYPE_COUNT] = {};

bool greaterthan(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func greaterthan_func = greaterthan_table[lhs][rhs];

    if(!greaterthan_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return greaterthan_func(left,right);
}

void init_greaterthan_table(){
    greaterthan_table[type::INT][type::INT] = greaterthan_int;
    greaterthan_table[type::VARCHAR][type::VARCHAR] = greaterthan_varchar;
    greaterthan_table[type::INT][type::VARCHAR] = greaterthan_int_varchar;
    greaterthan_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return greaterthan_int_varchar(r,l); // reverse args
    };
}

/***********************************lessthan or equalto operator implimentation *******************************/
bool lessthan_or_equal_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value <= static_cast<inttype*>(right)->value;
}

bool lessthan_or_equal_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value <= static_cast<varchar*>(right)->value;
}

bool lessthan_or_equal_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value <= std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func lessthan_or_equal_table[TYPE_COUNT][TYPE_COUNT] = {};

bool lessthan_or_equal(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func lessthan_or_equal_func = lessthan_or_equal_table[lhs][rhs];

    if(!lessthan_or_equal_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return lessthan_or_equal_func(left,right);
}

void init_lessthan_or_equal_table(){
    lessthan_or_equal_table[type::INT][type::INT] = lessthan_or_equal_int;
    lessthan_or_equal_table[type::VARCHAR][type::VARCHAR] = lessthan_or_equal_varchar;
    lessthan_or_equal_table[type::INT][type::VARCHAR] = lessthan_or_equal_int_varchar;
    lessthan_or_equal_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return lessthan_or_equal_int_varchar(r,l); // reverse args
    };
}

/*************************************greaterthan_or_equal_int*****************************************/

bool greaterthan_or_equal_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value >= static_cast<inttype*>(right)->value;
}

bool greaterthan_or_equal_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value >= static_cast<varchar*>(right)->value;
}

bool greaterthan_or_equal_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value >= std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func greaterthan_or_equal_table[TYPE_COUNT][TYPE_COUNT] = {};

bool greaterthan_or_equal(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func greaterthan_or_equal_func = greaterthan_or_equal_table[lhs][rhs];

    if(!greaterthan_or_equal_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return greaterthan_or_equal_func(left,right);
}

void init_greaterthan_or_equal_table(){
    greaterthan_or_equal_table[type::INT][type::INT] = greaterthan_or_equal_int;
    greaterthan_or_equal_table[type::VARCHAR][type::VARCHAR] = greaterthan_or_equal_varchar;
    greaterthan_or_equal_table[type::INT][type::VARCHAR] = greaterthan_or_equal_int_varchar;
    greaterthan_or_equal_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return greaterthan_or_equal_int_varchar(r,l); // reverse args
    };
}

/******************************notequal opearator implimentation ****************************************/
bool notequal_int(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value == static_cast<inttype*>(right)->value;
}

bool notequal_varchar(datatype* left,datatype* right){
    return static_cast<varchar*>(left)->value == static_cast<varchar*>(right)->value;
}

bool notequal_int_varchar(datatype* left,datatype* right){
    return static_cast<inttype*>(left)->value == std::stoi(static_cast<varchar*>(right)->value);
}

binary_op_func notequal_table[TYPE_COUNT][TYPE_COUNT] = {};

bool notequal(datatype* left,datatype* right){
    if(left == nullptr || right == nullptr) return false;

    type lhs = left->get_type();
    type rhs = right->get_type();

    binary_op_func notequal_func = notequal_table[lhs][rhs];

    if(!notequal_func){
        std::cerr<<"functionality for "<<left->get_type()<<" and "
        <<right->get_type()<<" not implimented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    return notequal_func(left,right);
}

void init_notequal_table(){
    notequal_table[type::INT][type::INT] = notequal_int;
    notequal_table[type::VARCHAR][type::VARCHAR] = notequal_varchar;
    notequal_table[type::INT][type::VARCHAR] = notequal_int_varchar;
    notequal_table[type::VARCHAR][type::INT] = [](datatype* l,datatype* r){
        return notequal_int_varchar(r,l); // reverse args
    };
}

/*************************************************************************************************************/

void init_op_tables(){
    init_eq_table();
    init_lessthan_table();
    init_greaterthan_table();
    init_lessthan_or_equal_table();
    init_greaterthan_or_equal_table();
    init_notequal_table();
}

/*route to corresponding comparator function*/

binary_op_func route_table[OPS_COUNT] = {
    [Ops::EQ]=equate,
    [Ops::LT]=lessthan,
    [Ops::GT]=greaterthan,
    [Ops::LTE]=lessthan_or_equal,
    [Ops::GTE]=greaterthan_or_equal,
    [Ops::NEQ]=notequal,
};

bool evaluate_and_comp(datatype* left,datatype* right,Ops op){
    return route_table[op](left,right);
}
