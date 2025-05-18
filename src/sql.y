/* -------------------------------------------------------------
   SQL-92 subset grammar – C backend (union) – builds with g++
   ------------------------------------------------------------- */
%{
#include <cstdio>
#include <cstdlib>
#include <cstring>

/* Forward declarations */
void yyerror (const char *s);
extern int  yylex (void);
%}

/* ----------------------------------------------------------------------------
   Bison settings
   --------------------------------------------------------------------------*/
%define api.token.prefix {TOKEN_}   /* lexer already returns TOKEN_* codes */

/* value type: a classic %union that matches what the lexer fills in */
%union {
    char   *str_val;
    int     int_val;
    double  float_val;
}

/* ----------------------------------------------------------------------------
   Token declarations
   --------------------------------------------------------------------------*/
%token SELECT FROM WHERE GROUP BY HAVING ORDER ASC DESC
%token JOIN INNER OUTER LEFT RIGHT FULL ON AS
%token AND OR NOT SQLNULL IS IN LIKE BETWEEN
%token CREATE TABLE INSERT INTO VALUES UPDATE SET DELETE
%token INT CHAR VARCHAR NUMBER DATE TEXT
%token PRIMARY KEY UNIQUE DEFAULT REFERENCES
%token EXISTS
%token LE GE NE                       /*  <=  >=  <> / !=  */
%token <str_val>   IDENTIFIER STRING_LITERAL
%token <int_val>   INTEGER_LITERAL
%token <float_val> FLOAT_LITERAL

/* precedence / associativity */
%left  OR
%left  AND
%right NOT
%right UMINUS
%nonassoc '=' '<' '>' LE GE NE

/* ----------------------------------------------------------------------------
   Grammar rules  (your original rules kept as–is)
   --------------------------------------------------------------------------*/
%%
input_statement
        : /* empty */
        | input_statement statement                 { /* ignore */ }
        ;

statement
        : select_statement ';'
        | /* add other statement types here */
        ;

select_statement
        : SELECT select_list FROM table_reference_list
          where_clause_opt group_by_clause_opt having_clause_opt
          order_by_clause_opt
        ;

select_list
        : '*'
        | select_item_list
        ;

select_item_list
        : select_item
        | select_item_list ',' select_item
        ;

select_item
        : expression
        | expression AS IDENTIFIER
        | expression IDENTIFIER
        ;

table_reference_list
    : table_reference
    | table_reference_list ',' table_reference
    ;

table_reference
    : table_name
    | table_name IDENTIFIER
    | table_name AS IDENTIFIER
    | table_reference join_type JOIN table_reference ON search_condition
    ;

table_name
    : IDENTIFIER
    /* | IDENTIFIER '.' IDENTIFIER */
    ;

join_type
    : /* empty = INNER */
    | INNER
    | LEFT
    | RIGHT
    | FULL
    | LEFT OUTER
    | RIGHT OUTER
    | FULL OUTER
    ;

where_clause_opt
    : /* empty */
    | WHERE search_condition
    ;

group_by_clause_opt
    : /* empty */
    | GROUP BY column_reference_list
    ;

column_reference_list
    : column_reference
    | column_reference_list ',' column_reference
    ;

column_reference
    : IDENTIFIER
    | table_name '.' IDENTIFIER
    ;

having_clause_opt
    : /* empty */
    | HAVING search_condition
    ;

order_by_clause_opt
    : /* empty */
    | ORDER BY order_by_list
    ;

order_by_list
    : order_by_item
    | order_by_list ',' order_by_item
    ;

order_by_item
    : expression
    | expression ASC
    | expression DESC
    ;

/* INSERT statement */
insert_statement
    : INSERT INTO table_name insert_columns_clause VALUES '(' insert_values_list ')'
    ;

insert_columns_clause
    : /* empty */
    | '(' column_reference_list ')'
    ;

insert_values_list
    : expression
    | insert_values_list ',' expression
    ;

/* UPDATE statement */
update_statement
    : UPDATE table_name SET update_list where_clause_opt
    ;

update_list
    : update_item
    | update_list ',' update_item
    ;

update_item
    : column_reference '=' expression
    ;

/* DELETE statement */
delete_statement
    : DELETE FROM table_name where_clause_opt
    ;

/* CREATE TABLE statement */
create_statement
    : CREATE TABLE table_name '(' column_definition_list ')'
    ;

column_definition_list
    : column_definition
    | column_definition_list ',' column_definition
    ;

column_definition
    : IDENTIFIER data_type column_constraint_list_opt
    ;

data_type
    : INT
    | CHAR '(' INTEGER_LITERAL ')'
    | VARCHAR '(' INTEGER_LITERAL ')'
    | NUMBER
    | DATE
    | TEXT
    ;

column_constraint_list_opt
    : /* empty */
    | column_constraint_list
    ;

column_constraint_list
    : column_constraint
    | column_constraint_list column_constraint
    ;

column_constraint
    : NOT SQLNULL
    | SQLNULL
    | PRIMARY KEY
    | UNIQUE
    | DEFAULT default_value
    | REFERENCES table_name
    ;

default_value
    : INTEGER_LITERAL
    | FLOAT_LITERAL
    | STRING_LITERAL
    | SQLNULL
    ;

/* Conditions */
search_condition
    : search_condition OR search_condition
    | search_condition AND search_condition
    | NOT search_condition
    | '(' search_condition ')'
    | predicate
    ;

predicate
    : comparison_predicate
    | between_predicate
    | in_predicate
    | like_predicate
    | null_predicate
    | exists_predicate
    ;

comparison_predicate
    : expression '=' expression
    | expression '<' expression
    | expression '>' expression
    | expression LE expression
    | expression GE expression
    | expression NE expression
    ;

between_predicate
    : expression BETWEEN expression AND expression
    | expression NOT BETWEEN expression AND expression
    ;

in_predicate
    : expression IN '(' expression_list ')'
    | expression NOT IN '(' expression_list ')'
    ;

like_predicate
    : expression LIKE expression
    | expression NOT LIKE expression
    ;

null_predicate
    : expression IS SQLNULL
    | expression IS NOT SQLNULL
    ;

exists_predicate
    : EXISTS '(' select_statement ')'
    | NOT EXISTS '(' select_statement ')'
    ;

/* Expressions */
expression_list
    : expression
    | expression_list ',' expression
    ;

expression
    : term
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | '-' expression %prec UMINUS
    | '(' expression ')'
    | function_call
    ;

term
    : IDENTIFIER
    | table_name '.' IDENTIFIER
    | INTEGER_LITERAL
    | FLOAT_LITERAL
    | STRING_LITERAL
    ;

function_call
    : IDENTIFIER '(' ')'
    | IDENTIFIER '(' function_arg_list ')'
    ;

function_arg_list
    : expression
    | function_arg_list ',' expression
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

