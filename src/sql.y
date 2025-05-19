/* -------------------------------------------------------------
   SQL-92 subset grammar – C backend (union) – builds with g++
   ------------------------------------------------------------- */
%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "include/ast.hpp"
#include "include/datatypes.hpp"

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
    AST* ast_node;
    select_node* select_statement_node;
    from_clause* table_ref_list;
    column_definition* colmn_def;
    create_table* create_tbl;
    datatype* dtype;
}

/* ----------------------------------------------------------------------------
   Token declarations
   --------------------------------------------------------------------------*/
%token SELECT FROM WHERE GROUP BY HAVING ORDER ASC DESC
%token JOIN INNER OUTER LEFT RIGHT FULL ON AS
%token AND OR NOT SQLNULL IS IN LIKE BETWEEN
%token CREATE TABLE INSERT INTO VALUES UPDATE SET DELETE
%token INT CHAR VARCHAR NUMBER DATE TEXT
%token PRIMARY KEY UNIQUE DEFAULT REFERENCES FOREIGN
%token EXISTS LIMIT OFFSET
%token LE GE NE                       /*  <=  >=  <> / !=  */
%token <str_val>   IDENTIFIER STRING_LITERAL
%token <int_val>   INTEGER_LITERAL
%token <float_val> FLOAT_LITERAL

%type <select_statement_node> select_statement
%type <table_ref_list> table_reference table_reference_list
%type <ast_node> select_item  select_list 
%type <ast_node> table_name 
%type <ast_node> expression term  
%type <ast_node> column_constraint column_constraint_list column_constraint_list_opt 
%type <create_tbl> create_statement 
%type <colmn_def> column_definition column_definition_list
%type <dtype> data_type default_value
/* precedence / associativity */
%left OR
%left AND
%right NOT
%nonassoc '=' '<' '>' LE GE NE
%nonassoc BETWEEN IN LIKE
%nonassoc EXISTS    
%left '+' '-'              
%left '*' '/'             
%right UMINUS

/* ----------------------------------------------------------------------------
   Grammar rules  
   --------------------------------------------------------------------------*/
%%
query
        : /* empty */
        | query sql_statement                 { /* ignore */ }
        ;

sql_statement
    : select_statement ';'{$1->print_select();}
    | insert_statement
    | update_statement
    | delete_statement
    | create_statement ';' {$1->print_table();}
    ;

select_statement
        : SELECT select_list FROM table_reference_list
          where_clause_opt group_by_clause_opt having_clause_opt
          order_by_clause_opt limit_clause_opt offset_clause_opt{
            /*phase 1*/
            // AST* select = new AST("select_statement");
            // AST* select_list_items = new AST("select_list");
            // select_list_items->ptr_children = $2;
            // select->ptr_children = select_list_items;
            // AST* from_clauses = new AST("from_clause");
            // from_clauses->ptr_children = $4;
            // select_list_items->ptr_sibling = from_clauses;
            // $$ = select;
            select_node* select = new select_node();
            select->select_list.reset($2);
            select->table_reference_list.reset($4);
            $$ = select;
        }
        ;

select_list
        : select_item {
            $$ = $1;
        }
        | select_list ',' select_item {
            AST* last = $1;
            while (last->ptr_sibling != nullptr) {
                last = last->ptr_sibling;
            }
            last->ptr_sibling = $3;
            $$ = $1;
        }
        ;

select_item
        : expression {
            $$ = $1;
        }
        | expression AS IDENTIFIER
        | expression IDENTIFIER
        ;

table_reference_list
    : table_reference {$$ = $1;}
    /* | table_reference_list ',' table_reference {
        $1->ptr_sibling = $3;
        $$ = $1;
     // cross join case
    } */
    ;

table_reference
    : table_name {
        from_clause* tbl_name = new from_clause();
        tbl_name->first_table.reset($1);
        $$ = tbl_name ;
    }
    | table_name IDENTIFIER {}
    | table_name AS IDENTIFIER {}
    | table_reference join_type JOIN table_reference ON search_condition {}
    ;

table_name
    : IDENTIFIER { 
        $$ = new AST(std::string($1)) ;
    }
    /* | IDENTIFIER '.' IDENTIFIER */
    ;

join_type
    : /* empty */
    | INNER
    | LEFT OUTER         
    | RIGHT OUTER
    | FULL OUTER
    | LEFT
    | RIGHT
    | FULL
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

limit_clause_opt
    : /* empty */
    | LIMIT expression    // Use LIMIT keyword

offset_clause_opt
    : /* empty */
    | OFFSET expression   // Use OFFSET keyword
    
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
    : CREATE TABLE table_name '(' column_definition_list ')' {
        create_table* table = new create_table();
        table->table_name.reset($3);
        table->columns_definitions=$5;
        /*extra expilicit table constraints*/
        $$ = table;
    }
    ;

column_definition_list
    : column_definition { $$ = $1;}
    | column_definition_list ',' column_definition{
        AST* last = (AST*)$1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = (AST*)$3;
        $$ = $1; 
    }
    ;

column_definition
    : IDENTIFIER data_type column_constraint_list_opt {
        column_definition* clmn_def = new column_definition();
        clmn_def->Column = std::string($1);
        clmn_def->Type.reset($2);
        clmn_def->constraints.reset($3);
        $$ = clmn_def;
    }
    ;

data_type
    : INT   {
        $$ = new inttype();
    }
    | CHAR '(' INTEGER_LITERAL ')' {
        // $$ = new 
    }
    | VARCHAR '(' INTEGER_LITERAL ')'{
        $$ = new varchar($3);
    }
    | NUMBER {

    }
    | DATE {

    }
    | TEXT {

    }
    ;

column_constraint_list_opt
    : /* empty */ { $$ = nullptr;}
    | column_constraint_list { $$ = $1;}
    ;

column_constraint_list
    : column_constraint { $$ = $1;}
    | column_constraint_list column_constraint {
        AST* last = $1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = $2;
        $$ = $1; 
    }
    ;

column_constraint
    : NOT SQLNULL {
        $$ = new AST("NOT NULL");
    }
    | SQLNULL {
        $$ = new AST("NULL");
    }
    | PRIMARY KEY {
        $$ = new AST("PRIMARY KEY");
    }
    | UNIQUE {
        $$ = new AST("UNIQUE");
    }
    | DEFAULT default_value {
        AST* type = new AST("DEFAULT");
        type->ptr_sibling = (AST*)$2;
        $$ = type;
    }
    | FOREIGN KEY REFERENCES table_name '(' IDENTIFIER ')' {
        AST* type = new AST("FOREIGN KEY");
        type->ptr_children = $4;
        type->ptr_children->ptr_sibling = new AST(std::string($6)) ;
        $$ = type;
    }
    ;

default_value
    : INTEGER_LITERAL {
        datatype* data = new inttype();
        ((inttype*)data)->value = $1;
        $$ = data;
    }
    /* | FLOAT_LITERAL   { $$ = new AST(std::to_string($1));} */
    | STRING_LITERAL  { 
        datatype* data = new varchar(10);
        ((varchar*)data)->value = std::string($1);
        $$ = data;
    }
    /* | SQLNULL         { $$ = new AST(std::to_string($1));} */
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
    /* Removed the conflicting rule: | NOT EXISTS '(' select_statement ')' */
    ;

/* Expressions */
expression_list
    : expression
    | expression_list ',' expression
    ;

expression
    : term { $$ = $1;}
    | expression '+' expression {}
    | expression '-' expression {}
    | expression '*' expression {}
    | expression '/' expression {}
    | '-' expression %prec UMINUS {}
    | '(' expression ')' {}
    | function_call {}
    ;

term
    : IDENTIFIER   {
        $$ = new AST(std::string($1)) ;;
    }
    | table_name '.' IDENTIFIER {}
    | INTEGER_LITERAL {}
    | FLOAT_LITERAL {}
    | STRING_LITERAL {}
    | '*'{
        $$ = new AST("*") ;
    }
    ;

function_call
    : IDENTIFIER '(' ')' {}
    | IDENTIFIER '(' function_arg_list ')' {}
    ;

function_arg_list
    : expression {}
    | function_arg_list ',' expression {}
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}