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
#include "include/query_processor.hpp"
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
    insert_stmt* insert;
    column_constraints* clmn_constrnt;
    condition* search_cond;
}

/* ----------------------------------------------------------------------------
   Token declarations
   --------------------------------------------------------------------------*/
%token SELECT FROM WHERE GROUP BY HAVING ORDER ASC DESC
%token JOIN INNER OUTER LEFT RIGHT FULL ON AS
%token AND OR NOT SQLNULL IS IN LIKE BETWEEN
%token CREATE TABLE INSERT INTO VALUES UPDATE SET DELETE DATABASE CREATEDB
%token INT CHAR VARCHAR NUMBER DATE TEXT
%token PRIMARY KEY UNIQUE DEFAULT REFERENCES FOREIGN
%token EXISTS LIMIT OFFSET DROP
%token LE GE NE                       /*  <=  >=  <> / !=  */
%token <str_val>   IDENTIFIER STRING_LITERAL
%token <int_val>   INTEGER_LITERAL
%token <float_val> FLOAT_LITERAL

%type <select_statement_node> select_statement
%type <table_ref_list> table_reference table_reference_list
%type <ast_node> select_item  select_list 
%type <ast_node> table_name drop_table
%type <ast_node> expression term  
%type <clmn_constrnt> column_constraint column_constraint_list column_constraint_list_opt 
%type <create_tbl> create_statement 
%type <colmn_def> column_definition column_definition_list
%type <dtype> data_type default_value
%type <insert> insert_statement
%type <ast_node> insert_columns_clause insert_values_list column_reference column_reference_list
%type <search_cond> where_clause_opt search_condition predicate comparison_predicate 
%type <ast_node> update_item update_list update_statement delete_statement insert_tuples tuples create_database drop_database
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
    : select_statement ';'{$1->print_select();query_executor.process_select_stmt($1);}
    | insert_statement ';' {$1->print_insert();query_executor.process_insert_stmt($1);}
    | update_statement ';' {((update*)$1)->print_update();}  
    | delete_statement  ';' {((Delete*)$1)->print_delete();}
    | create_statement ';' {$1->print_table();query_executor.process_create_table($1);}
    | drop_table ';' {$1->print_ast(0);}
    | create_database ';' {((create_database*)$1)->print_db();}
    | drop_database ';' {((drop_database*)$1)->print_drop();} 
    ;

select_statement
        : SELECT select_list FROM table_reference_list
          where_clause_opt group_by_clause_opt having_clause_opt
          order_by_clause_opt limit_clause_opt offset_clause_opt{
            /*phase 1*/
            select_node* select = new select_node();
            select->select_list.reset($2);
            select->table_reference_list.reset($4);
            select->where_clause.reset($5);
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
        | expression AS IDENTIFIER {

        }
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
    | table_name IDENTIFIER {
        
    }
    | table_name AS IDENTIFIER {

    }
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
    : /* empty */ {$$ = nullptr;}
    | WHERE search_condition {
        $$ = $2;
    }
    ;

group_by_clause_opt
    : /* empty */
    | GROUP BY column_reference_list
    ;

column_reference_list
    : column_reference { $$ = $1;}
    | column_reference_list ',' column_reference {
        AST* last = $1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = $3;
        $$ = $1;
    }
    ;

column_reference
    : IDENTIFIER {
        $$ = new AST(std::string($1));
    }
    | table_name '.' IDENTIFIER {

    }
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
    : INSERT INTO table_name insert_columns_clause VALUES insert_tuples {
        insert_stmt* insert_instance = new insert_stmt();
        insert_instance->table_name.reset($3);
        insert_instance->columns_to_insert = $4 ;
        insert_instance->values = $6;
        $$ = insert_instance;
    }
    ;

insert_columns_clause
    : /* empty */ { $$ = nullptr;}
    | '(' column_reference_list ')' {
        $$ = $2;
    }
    ;

insert_tuples
    : tuples { $$ = $1;}
    | insert_tuples ',' tuples { 
        AST* last = $1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = $3;
        $$ = $1;
    }
    ;

tuples : '(' insert_values_list ')' {
    AST* tuple = new AST(nodetype::TUPLE);
    tuple->ptr_children = $2;
    $$ = tuple;
    }
    ;

insert_values_list
    : expression { $$ = $1 ;}
    | insert_values_list ',' expression {
        AST* last = $1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = $3;
        $$ = $1;
    }
    ;

/* UPDATE statement */
update_statement
    : UPDATE table_name SET update_list where_clause_opt {
        update* update_stmt = new update();
        update_stmt->table_name.reset($2);
        update_stmt->update_list = $4;
        update_stmt->where_clause.reset($5);
        $$ = update_stmt;
    }
    ;

update_list
    : update_item {
        $$ = $1;
    }
    | update_list ',' update_item {
        AST* last = $1;
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = $3;
        $$ = $1;
    }
    ;

update_item
    : column_reference '=' expression {
        AST* item = new AST("set_value");
        item->ptr_children = $1;
        $1->ptr_sibling = $3;
        $$ = $1;
    }
    ;

/* DELETE statement */
delete_statement
    : DELETE FROM table_name where_clause_opt {
        Delete* stmt = new Delete();
        stmt->table_name.reset($3);
        stmt->where_clause.reset($4);
        $$ = stmt; 
    }
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
        column_constraints* last = $1;
        while (last->next_constraint != nullptr) {
            last = last->next_constraint;
        }
        last->next_constraint = $2;
        $$ = $1; 
    }
    ;

column_constraint
    : NOT SQLNULL {
        $$ = new not_null();
    }
    /* | SQLNULL {
        $$ = new AST("NULL");
    } */
    | PRIMARY KEY {
        $$ = new primary_key();
    }
    /* | UNIQUE {
        $$ = new unique_key();
    } */
    | DEFAULT default_value {
        $$ = new default_value($2);
    }
    /* | FOREIGN KEY REFERENCES table_name '(' IDENTIFIER ')' {
        AST* type = new AST("FOREIGN KEY");
        type->ptr_children = $4;
        type->ptr_children->ptr_sibling = new AST(std::string($6)) ;
        $$ = type;
    } */
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

/*drop table */
drop_table
    : DROP table_name {
        AST* drop = new AST("DROP TABLE");
        drop->ptr_children = $2;
        $$ = drop;
    }

/* Conditions */
search_condition
    : search_condition OR search_condition {}
    | search_condition AND search_condition{}
    | NOT search_condition{}
    | '(' search_condition ')'{}
    | predicate {
        $$ = $1;
    }
    ;

predicate
    : comparison_predicate {
        $$ = $1;
    }
    | between_predicate{}
    | in_predicate{}
    | like_predicate{}
    | null_predicate{}
    | exists_predicate{}
    ;

comparison_predicate
    : expression '=' expression{
        $$ = new comparison($1,$3,Ops::EQ);
    }
    | expression '<' expression{
        $$ = new comparison($1,$3,Ops::LT);
    }
    | expression '>' expression{
        $$ = new comparison($1,$3,Ops::GT);
    }
    | expression LE expression{
        $$ = new comparison($1,$3,Ops::LTE);
    }
    | expression GE expression{
        $$ = new comparison($1,$3,Ops::GTE);
    }
    | expression NE expression{
        $$ = new comparison($1,$3,Ops::NEQ);
    }
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
        $$ = new AST(std::string($1),tbl_or_col) ;

    }
    | table_name '.' IDENTIFIER {}
    | INTEGER_LITERAL {
        datatype* data = new inttype();
        ((inttype*)data)->value = $1;
        AST* intnode = new AST(val);
        intnode->ptr_children = (AST*)data;
        $$ = intnode;
    }
    | FLOAT_LITERAL {
        // $$ = new AST(std::to_string($1));
    }
    | STRING_LITERAL {
        datatype* data = new varchar(10);
        ((varchar*)data)->value = std::string($1);
        AST* strnode = new AST(val);
        strnode->ptr_children = (AST*)data;
        $$ = strnode;
    }
    | '*'{
        $$ = new AST("*") ;
    }
    ;

create_database : CREATE DATABASE IDENTIFIER {
        AST* db = new create_database(std::string($3));
        $$ = db;
    }
    | CREATEDB IDENTIFIER {
        AST* db = new create_database(std::string($2));
        $$ = db;
    }
    ;
drop_database : DROP DATABASE IDENTIFIER {
        AST* db = new drop_database(std::string($3));
        $$ = db;
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