/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_SQL_TAB_HPP_INCLUDED
# define YY_YY_BUILD_SQL_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_YYEMPTY = -2,
    TOKEN_YYEOF = 0,               /* "end of file"  */
    TOKEN_YYerror = 256,           /* error  */
    TOKEN_YYUNDEF = 257,           /* "invalid token"  */
    TOKEN_SELECT = 258,            /* SELECT  */
    TOKEN_FROM = 259,              /* FROM  */
    TOKEN_WHERE = 260,             /* WHERE  */
    TOKEN_GROUP = 261,             /* GROUP  */
    TOKEN_BY = 262,                /* BY  */
    TOKEN_HAVING = 263,            /* HAVING  */
    TOKEN_ORDER = 264,             /* ORDER  */
    TOKEN_ASC = 265,               /* ASC  */
    TOKEN_DESC = 266,              /* DESC  */
    TOKEN_JOIN = 267,              /* JOIN  */
    TOKEN_INNER = 268,             /* INNER  */
    TOKEN_OUTER = 269,             /* OUTER  */
    TOKEN_LEFT = 270,              /* LEFT  */
    TOKEN_RIGHT = 271,             /* RIGHT  */
    TOKEN_FULL = 272,              /* FULL  */
    TOKEN_ON = 273,                /* ON  */
    TOKEN_AS = 274,                /* AS  */
    TOKEN_AND = 275,               /* AND  */
    TOKEN_OR = 276,                /* OR  */
    TOKEN_NOT = 277,               /* NOT  */
    TOKEN_SQLNULL = 278,           /* SQLNULL  */
    TOKEN_IS = 279,                /* IS  */
    TOKEN_IN = 280,                /* IN  */
    TOKEN_LIKE = 281,              /* LIKE  */
    TOKEN_BETWEEN = 282,           /* BETWEEN  */
    TOKEN_CREATE = 283,            /* CREATE  */
    TOKEN_TABLE = 284,             /* TABLE  */
    TOKEN_INSERT = 285,            /* INSERT  */
    TOKEN_INTO = 286,              /* INTO  */
    TOKEN_VALUES = 287,            /* VALUES  */
    TOKEN_UPDATE = 288,            /* UPDATE  */
    TOKEN_SET = 289,               /* SET  */
    TOKEN_DELETE = 290,            /* DELETE  */
    TOKEN_INT = 291,               /* INT  */
    TOKEN_CHAR = 292,              /* CHAR  */
    TOKEN_VARCHAR = 293,           /* VARCHAR  */
    TOKEN_NUMBER = 294,            /* NUMBER  */
    TOKEN_DATE = 295,              /* DATE  */
    TOKEN_TEXT = 296,              /* TEXT  */
    TOKEN_PRIMARY = 297,           /* PRIMARY  */
    TOKEN_KEY = 298,               /* KEY  */
    TOKEN_UNIQUE = 299,            /* UNIQUE  */
    TOKEN_DEFAULT = 300,           /* DEFAULT  */
    TOKEN_REFERENCES = 301,        /* REFERENCES  */
    TOKEN_FOREIGN = 302,           /* FOREIGN  */
    TOKEN_EXISTS = 303,            /* EXISTS  */
    TOKEN_LIMIT = 304,             /* LIMIT  */
    TOKEN_OFFSET = 305,            /* OFFSET  */
    TOKEN_DROP = 306,              /* DROP  */
    TOKEN_LE = 307,                /* LE  */
    TOKEN_GE = 308,                /* GE  */
    TOKEN_NE = 309,                /* NE  */
    TOKEN_IDENTIFIER = 310,        /* IDENTIFIER  */
    TOKEN_STRING_LITERAL = 311,    /* STRING_LITERAL  */
    TOKEN_INTEGER_LITERAL = 312,   /* INTEGER_LITERAL  */
    TOKEN_FLOAT_LITERAL = 313,     /* FLOAT_LITERAL  */
    TOKEN_UMINUS = 314             /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "src/sql.y"

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

#line 136 "build/sql.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_SQL_TAB_HPP_INCLUDED  */
