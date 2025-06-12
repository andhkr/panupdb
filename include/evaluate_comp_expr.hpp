#ifndef EVALUATE_COMP_EXPR_HPP
#define EVALUATE_COMP_EXPR_HPP

#include "datatypes.hpp"
/*first i am implimenting comparing evaluated expr*/
using binary_op_func = bool (*) (datatype*,datatype*);

/********************************equal[=] operator implementation*********************************/
bool equate_int(datatype* left,datatype* right);

bool equate_varchar(datatype* left,datatype* right);

bool equate_int_varchar(datatype* left,datatype* right);

extern binary_op_func eq_table[TYPE_COUNT][TYPE_COUNT];

bool equate(datatype* left,datatype* right);

void init_eq_table();

/*******************************************lessthan[<] operator *******************************************/

bool lessthan_int(datatype* left,datatype* right);

bool lessthan_varchar(datatype* left,datatype* right);

bool lessthan_int_varchar(datatype* left,datatype* right);

extern binary_op_func lessthan_table[TYPE_COUNT][TYPE_COUNT];

bool lessthan(datatype* left,datatype* right);

void init_lessthan_table();

/****************************************greater than [>] opearator implementation ************************/
bool greaterthan_int(datatype* left,datatype* right);

bool greaterthan_varchar(datatype* left,datatype* right);

bool greaterthan_int_varchar(datatype* left,datatype* right);

extern binary_op_func greaterthan_table[TYPE_COUNT][TYPE_COUNT];

bool greaterthan(datatype* left,datatype* right);

void init_greaterthan_table();

/***********************************lessthan or equalto operator implimentation *******************************/
bool lessthan_or_equal_int(datatype* left,datatype* right);

bool lessthan_or_equal_varchar(datatype* left,datatype* right);

bool lessthan_or_equal_int_varchar(datatype* left,datatype* right);

extern binary_op_func lessthan_or_equal_table[TYPE_COUNT][TYPE_COUNT];

bool lessthan_or_equal(datatype* left,datatype* right);

void init_lessthan_or_equal_table();

/*************************************greaterthan_or_equal_int*****************************************/

bool greaterthan_or_equal_int(datatype* left,datatype* right);

bool greaterthan_or_equal_varchar(datatype* left,datatype* right);

bool greaterthan_or_equal_int_varchar(datatype* left,datatype* right);

extern binary_op_func greaterthan_or_equal_table[TYPE_COUNT][TYPE_COUNT];

bool greaterthan_or_equal(datatype* left,datatype* right);

void init_greaterthan_or_equal_table();

/******************************notequal opearator implimentation ****************************************/
bool notequal_int(datatype* left,datatype* right);

bool notequal_varchar(datatype* left,datatype* right);

bool notequal_int_varchar(datatype* left,datatype* right);

extern binary_op_func notequal_table[TYPE_COUNT][TYPE_COUNT];

extern bool notequal(datatype* left,datatype* right);

void init_notequal_table();

/*************************************************************************************************************/
void init_op_tables();

/*route to corresponding comparator function*/

extern binary_op_func route_table[OPS_COUNT];

extern bool evaluate_and_comp(datatype* left,datatype* right,Ops op);

#endif