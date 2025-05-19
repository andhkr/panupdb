/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "src/sql.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "include/ast.hpp"
#include "include/datatypes.hpp"

/* Forward declarations */
void yyerror (const char *s);
extern int  yylex (void);

#line 84 "build/sql.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sql.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SELECT = 3,                     /* SELECT  */
  YYSYMBOL_FROM = 4,                       /* FROM  */
  YYSYMBOL_WHERE = 5,                      /* WHERE  */
  YYSYMBOL_GROUP = 6,                      /* GROUP  */
  YYSYMBOL_BY = 7,                         /* BY  */
  YYSYMBOL_HAVING = 8,                     /* HAVING  */
  YYSYMBOL_ORDER = 9,                      /* ORDER  */
  YYSYMBOL_ASC = 10,                       /* ASC  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_JOIN = 12,                      /* JOIN  */
  YYSYMBOL_INNER = 13,                     /* INNER  */
  YYSYMBOL_OUTER = 14,                     /* OUTER  */
  YYSYMBOL_LEFT = 15,                      /* LEFT  */
  YYSYMBOL_RIGHT = 16,                     /* RIGHT  */
  YYSYMBOL_FULL = 17,                      /* FULL  */
  YYSYMBOL_ON = 18,                        /* ON  */
  YYSYMBOL_AS = 19,                        /* AS  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_SQLNULL = 23,                   /* SQLNULL  */
  YYSYMBOL_IS = 24,                        /* IS  */
  YYSYMBOL_IN = 25,                        /* IN  */
  YYSYMBOL_LIKE = 26,                      /* LIKE  */
  YYSYMBOL_BETWEEN = 27,                   /* BETWEEN  */
  YYSYMBOL_CREATE = 28,                    /* CREATE  */
  YYSYMBOL_TABLE = 29,                     /* TABLE  */
  YYSYMBOL_INSERT = 30,                    /* INSERT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_UPDATE = 33,                    /* UPDATE  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_DELETE = 35,                    /* DELETE  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_CHAR = 37,                      /* CHAR  */
  YYSYMBOL_VARCHAR = 38,                   /* VARCHAR  */
  YYSYMBOL_NUMBER = 39,                    /* NUMBER  */
  YYSYMBOL_DATE = 40,                      /* DATE  */
  YYSYMBOL_TEXT = 41,                      /* TEXT  */
  YYSYMBOL_PRIMARY = 42,                   /* PRIMARY  */
  YYSYMBOL_KEY = 43,                       /* KEY  */
  YYSYMBOL_UNIQUE = 44,                    /* UNIQUE  */
  YYSYMBOL_DEFAULT = 45,                   /* DEFAULT  */
  YYSYMBOL_REFERENCES = 46,                /* REFERENCES  */
  YYSYMBOL_FOREIGN = 47,                   /* FOREIGN  */
  YYSYMBOL_EXISTS = 48,                    /* EXISTS  */
  YYSYMBOL_LIMIT = 49,                     /* LIMIT  */
  YYSYMBOL_OFFSET = 50,                    /* OFFSET  */
  YYSYMBOL_DROP = 51,                      /* DROP  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_IDENTIFIER = 55,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 56,            /* STRING_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 57,           /* INTEGER_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 58,             /* FLOAT_LITERAL  */
  YYSYMBOL_59_ = 59,                       /* '='  */
  YYSYMBOL_60_ = 60,                       /* '<'  */
  YYSYMBOL_61_ = 61,                       /* '>'  */
  YYSYMBOL_62_ = 62,                       /* '+'  */
  YYSYMBOL_63_ = 63,                       /* '-'  */
  YYSYMBOL_64_ = 64,                       /* '*'  */
  YYSYMBOL_65_ = 65,                       /* '/'  */
  YYSYMBOL_UMINUS = 66,                    /* UMINUS  */
  YYSYMBOL_67_ = 67,                       /* ';'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '.'  */
  YYSYMBOL_70_ = 70,                       /* '('  */
  YYSYMBOL_71_ = 71,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_query = 73,                     /* query  */
  YYSYMBOL_sql_statement = 74,             /* sql_statement  */
  YYSYMBOL_select_statement = 75,          /* select_statement  */
  YYSYMBOL_select_list = 76,               /* select_list  */
  YYSYMBOL_select_item = 77,               /* select_item  */
  YYSYMBOL_table_reference_list = 78,      /* table_reference_list  */
  YYSYMBOL_table_reference = 79,           /* table_reference  */
  YYSYMBOL_table_name = 80,                /* table_name  */
  YYSYMBOL_join_type = 81,                 /* join_type  */
  YYSYMBOL_where_clause_opt = 82,          /* where_clause_opt  */
  YYSYMBOL_group_by_clause_opt = 83,       /* group_by_clause_opt  */
  YYSYMBOL_column_reference_list = 84,     /* column_reference_list  */
  YYSYMBOL_column_reference = 85,          /* column_reference  */
  YYSYMBOL_having_clause_opt = 86,         /* having_clause_opt  */
  YYSYMBOL_order_by_clause_opt = 87,       /* order_by_clause_opt  */
  YYSYMBOL_order_by_list = 88,             /* order_by_list  */
  YYSYMBOL_order_by_item = 89,             /* order_by_item  */
  YYSYMBOL_limit_clause_opt = 90,          /* limit_clause_opt  */
  YYSYMBOL_offset_clause_opt = 91,         /* offset_clause_opt  */
  YYSYMBOL_insert_statement = 92,          /* insert_statement  */
  YYSYMBOL_insert_columns_clause = 93,     /* insert_columns_clause  */
  YYSYMBOL_insert_values_list = 94,        /* insert_values_list  */
  YYSYMBOL_update_statement = 95,          /* update_statement  */
  YYSYMBOL_update_list = 96,               /* update_list  */
  YYSYMBOL_update_item = 97,               /* update_item  */
  YYSYMBOL_delete_statement = 98,          /* delete_statement  */
  YYSYMBOL_create_statement = 99,          /* create_statement  */
  YYSYMBOL_column_definition_list = 100,   /* column_definition_list  */
  YYSYMBOL_column_definition = 101,        /* column_definition  */
  YYSYMBOL_data_type = 102,                /* data_type  */
  YYSYMBOL_column_constraint_list_opt = 103, /* column_constraint_list_opt  */
  YYSYMBOL_column_constraint_list = 104,   /* column_constraint_list  */
  YYSYMBOL_column_constraint = 105,        /* column_constraint  */
  YYSYMBOL_default_value = 106,            /* default_value  */
  YYSYMBOL_drop_table = 107,               /* drop_table  */
  YYSYMBOL_search_condition = 108,         /* search_condition  */
  YYSYMBOL_predicate = 109,                /* predicate  */
  YYSYMBOL_comparison_predicate = 110,     /* comparison_predicate  */
  YYSYMBOL_between_predicate = 111,        /* between_predicate  */
  YYSYMBOL_in_predicate = 112,             /* in_predicate  */
  YYSYMBOL_like_predicate = 113,           /* like_predicate  */
  YYSYMBOL_null_predicate = 114,           /* null_predicate  */
  YYSYMBOL_exists_predicate = 115,         /* exists_predicate  */
  YYSYMBOL_expression_list = 116,          /* expression_list  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_term = 118,                     /* term  */
  YYSYMBOL_function_call = 119,            /* function_call  */
  YYSYMBOL_function_arg_list = 120         /* function_arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      70,    71,    64,    62,    68,    63,    69,    65,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    67,
      60,    59,    61,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    79,    83,    84,    85,    86,    87,    88,
      92,   104,   107,   118,   121,   122,   126,   135,   140,   141,
     142,   146,   153,   154,   155,   156,   157,   158,   159,   160,
     164,   165,   169,   170,   174,   175,   186,   189,   195,   196,
     200,   201,   205,   206,   210,   211,   212,   216,   217,   220,
     221,   225,   235,   236,   242,   243,   255,   261,   264,   270,
     277,   284,   294,   295,   306,   316,   319,   322,   325,   328,
     331,   337,   338,   342,   343,   354,   357,   360,   363,   366,
     371,   380,   386,   396,   404,   405,   406,   407,   408,   412,
     413,   414,   415,   416,   417,   421,   422,   423,   424,   425,
     426,   430,   431,   435,   436,   440,   441,   445,   446,   450,
     456,   457,   461,   462,   463,   464,   465,   466,   467,   468,
     472,   475,   476,   483,   486,   493,   499,   500,   504,   505
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SELECT", "FROM",
  "WHERE", "GROUP", "BY", "HAVING", "ORDER", "ASC", "DESC", "JOIN",
  "INNER", "OUTER", "LEFT", "RIGHT", "FULL", "ON", "AS", "AND", "OR",
  "NOT", "SQLNULL", "IS", "IN", "LIKE", "BETWEEN", "CREATE", "TABLE",
  "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE", "INT", "CHAR",
  "VARCHAR", "NUMBER", "DATE", "TEXT", "PRIMARY", "KEY", "UNIQUE",
  "DEFAULT", "REFERENCES", "FOREIGN", "EXISTS", "LIMIT", "OFFSET", "DROP",
  "LE", "GE", "NE", "IDENTIFIER", "STRING_LITERAL", "INTEGER_LITERAL",
  "FLOAT_LITERAL", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "';'", "','", "'.'", "'('", "')'", "$accept", "query",
  "sql_statement", "select_statement", "select_list", "select_item",
  "table_reference_list", "table_reference", "table_name", "join_type",
  "where_clause_opt", "group_by_clause_opt", "column_reference_list",
  "column_reference", "having_clause_opt", "order_by_clause_opt",
  "order_by_list", "order_by_item", "limit_clause_opt",
  "offset_clause_opt", "insert_statement", "insert_columns_clause",
  "insert_values_list", "update_statement", "update_list", "update_item",
  "delete_statement", "create_statement", "column_definition_list",
  "column_definition", "data_type", "column_constraint_list_opt",
  "column_constraint_list", "column_constraint", "default_value",
  "drop_table", "search_condition", "predicate", "comparison_predicate",
  "between_predicate", "in_predicate", "like_predicate", "null_predicate",
  "exists_predicate", "expression_list", "expression", "term",
  "function_call", "function_arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-23)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -98,    51,   -98,   131,    -4,     2,   -18,    35,   -18,   -98,
     -24,   -19,   -98,   -98,   -15,   -11,    -9,   -98,   -98,   -98,
     131,   -98,   131,    -1,   -98,     9,    70,   -98,   -98,   -18,
     -18,   -98,    37,   -18,   -98,   -98,   -98,   -98,   -98,   127,
     -98,   141,   -18,   131,    14,    25,   -98,   131,   131,   131,
     131,    13,    15,    39,    92,   -98,   -49,   -50,   -98,    92,
     218,     3,   -98,   -98,   -98,    23,    23,   -98,   -98,    54,
      39,    83,    47,    69,    61,     0,   -98,    48,   -98,   131,
     -98,   133,   -98,   149,   150,   151,   154,   112,   -98,   184,
     -48,   -98,   -41,   -98,    99,   115,   131,    39,   -98,    48,
     104,    48,    71,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     189,   -49,   168,   169,   -98,   -98,   -98,   -18,   -98,   -98,
     122,   123,   -98,   -98,   -98,   -13,    54,   -98,    39,   -98,
     131,   -98,   -49,   -98,   -98,   193,   -14,    97,    48,    48,
      74,    85,   130,   131,   131,   131,   131,   131,   131,   131,
     131,    39,    48,   198,   113,   160,   170,   205,   -98,   186,
     -98,    57,   194,   -98,   -13,   -98,   -98,   -98,   -33,   -49,
     165,   -98,   -98,   219,   174,   131,   131,   217,   -98,   131,
     -49,    90,   -49,   -49,   -49,   -49,   -49,   -49,   177,    71,
     239,   206,    48,   176,   185,   -98,   -98,   -98,   -98,   -98,
     211,   -98,   131,   -98,   -98,   131,   -49,   116,   -98,     4,
     -49,   131,   131,   131,   208,    71,   -98,   -98,   -18,   -49,
       6,   131,   131,   -98,   -49,   191,   -98,     1,   -49,   131,
     -98,   190,   -98,   -49,   -49,   131,   -98,   -98,   -49,   207,
     -98,   192,   -98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     6,     7,     0,     0,   120,   124,   122,   123,
       0,   125,     0,     0,    11,     0,    13,   112,   119,     0,
       0,    21,     0,     0,    83,     4,     5,     8,     9,     0,
     117,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,    52,     0,    30,   126,   128,     0,   118,    30,
      16,    17,    12,   121,    14,   113,   114,   115,   116,     0,
       0,     0,    36,     0,     0,    30,    57,     0,    60,     0,
     127,    32,    23,    27,    28,    29,     0,     0,    18,     0,
       0,    62,     0,    34,     0,     0,     0,     0,    56,     0,
       0,     0,    31,    88,    89,    90,    91,    92,    93,    94,
       0,   129,     0,    38,    24,    25,    26,     0,    19,    65,
       0,     0,    68,    69,    70,    71,     0,    61,     0,    53,
       0,    37,    59,    58,    86,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    22,     0,     0,     0,    76,     0,
      78,     0,     0,    64,    72,    73,    63,    35,     0,    54,
       0,    87,    85,    84,     0,     0,     0,     0,   107,     0,
     105,     0,    98,    99,   100,    95,    96,    97,    33,    39,
       0,    47,     0,     0,     0,    75,    77,    82,    81,    79,
       0,    74,     0,    51,   109,     0,   106,     0,   108,     0,
     110,     0,     0,     0,    49,    20,    66,    67,     0,    55,
       0,     0,     0,   103,   101,    41,    42,    44,    48,     0,
      10,     0,   104,   102,   111,     0,    45,    46,    50,     0,
      43,     0,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -98,   -98,   -98,   126,   -98,   221,   -98,   148,    20,   -98,
     -51,   -98,   117,   -69,   -98,   -98,   -98,    31,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   172,   -98,   -98,   -98,   144,
     -98,   -98,   -98,   103,   -98,   -98,   -97,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,    66,    -3,   -98,   -98,   -98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     9,    10,    23,    24,    59,    60,    25,    86,
      78,   113,    92,    74,   153,   191,   225,   226,   214,   230,
      11,    71,   168,    12,    75,    76,    13,    14,    90,    91,
     125,   163,   164,   165,   199,    15,   102,   103,   104,   105,
     106,   107,   108,   109,   209,   110,    27,    28,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    93,   134,    42,   136,    77,   138,   139,    81,   157,
     158,   236,   237,    47,    48,    49,    50,    40,    79,    41,
     126,    80,    87,   127,    98,    29,    32,   128,    34,   159,
     129,   160,   161,    30,   162,   202,    56,    31,   203,    33,
      26,   172,   173,    35,    65,    66,    67,    68,    36,    51,
      52,     2,    37,    54,     3,   189,    38,   171,    88,   167,
     -21,    39,    61,    47,    48,    49,    50,    43,    97,    63,
      99,    53,   222,    73,   222,   223,   111,   232,    44,     4,
      64,     5,    93,    69,     6,    70,     7,    49,    50,    45,
      73,   138,   139,   132,    72,   215,   100,    77,   137,   174,
     175,   176,     8,    16,    17,    18,    19,   177,   178,    89,
     211,    20,    21,   197,   198,    94,   -21,    73,   101,   140,
      96,   141,   142,   143,   144,    46,    82,   169,    83,    84,
      85,   192,    47,    48,    49,    50,   221,    61,    95,   112,
     180,   181,   182,   183,   184,   185,   186,   187,    73,   145,
     146,   147,    47,    48,    49,    50,   148,   149,   150,    47,
      48,    49,    50,   114,   115,   116,   117,   118,    58,   130,
     131,    73,   206,   207,   135,   151,   210,   152,    47,    48,
      49,    50,    16,    17,    18,    19,    16,    17,    18,    19,
      20,    21,   155,   156,    20,    21,     3,    22,    55,   219,
     179,    22,   210,    47,    48,    49,    50,   190,   224,   227,
     228,   140,    58,   141,   142,   143,   144,   193,   233,   234,
     119,   120,   121,   122,   123,   124,   238,   194,   195,   196,
     -22,    82,   227,    83,    84,    85,   204,   200,   231,   138,
     208,   145,   146,   147,   205,   128,   212,   216,   148,   149,
     150,    47,    48,    49,    50,   213,   217,   218,   229,   235,
     239,   170,   241,   242,    62,   154,   240,   201,   188,   133,
     166,   220
};

static const yytype_uint8 yycheck[] =
{
       3,    70,    99,     4,   101,     5,    20,    21,    59,    22,
      23,    10,    11,    62,    63,    64,    65,    20,    68,    22,
      68,    71,    19,    71,    75,    29,     6,    68,     8,    42,
      71,    44,    45,    31,    47,    68,    39,    55,    71,     4,
      43,   138,   139,    67,    47,    48,    49,    50,    67,    29,
      30,     0,    67,    33,     3,   152,    67,    71,    55,   128,
      69,    70,    42,    62,    63,    64,    65,    68,    68,    55,
      22,    34,    68,    53,    68,    71,    79,    71,    69,    28,
      55,    30,   151,    70,    33,    70,    35,    64,    65,    19,
      70,    20,    21,    96,    55,   192,    48,     5,   101,    25,
      26,    27,    51,    55,    56,    57,    58,    22,    23,    55,
      20,    63,    64,    56,    57,    32,    69,    97,    70,    22,
      59,    24,    25,    26,    27,    55,    13,   130,    15,    16,
      17,    18,    62,    63,    64,    65,    20,   117,    69,     6,
     143,   144,   145,   146,   147,   148,   149,   150,   128,    52,
      53,    54,    62,    63,    64,    65,    59,    60,    61,    62,
      63,    64,    65,    14,    14,    14,    12,    55,    71,    70,
      55,   151,   175,   176,    70,     7,   179,     8,    62,    63,
      64,    65,    55,    56,    57,    58,    55,    56,    57,    58,
      63,    64,    70,    70,    63,    64,     3,    70,    71,   202,
      70,    70,   205,    62,    63,    64,    65,     9,   211,   212,
     213,    22,    71,    24,    25,    26,    27,    57,   221,   222,
      36,    37,    38,    39,    40,    41,   229,    57,    23,    43,
      12,    13,   235,    15,    16,    17,    71,    43,   218,    20,
      23,    52,    53,    54,    70,    68,     7,    71,    59,    60,
      61,    62,    63,    64,    65,    49,    71,    46,    50,    68,
      70,   135,    55,    71,    43,   117,   235,   164,   151,    97,
     126,   205
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,     3,    28,    30,    33,    35,    51,    74,
      75,    92,    95,    98,    99,   107,    55,    56,    57,    58,
      63,    64,    70,    76,    77,    80,   117,   118,   119,    29,
      31,    55,    80,     4,    80,    67,    67,    67,    67,    70,
     117,   117,     4,    68,    69,    19,    55,    62,    63,    64,
      65,    80,    80,    34,    80,    71,   117,   120,    71,    78,
      79,    80,    77,    55,    55,   117,   117,   117,   117,    70,
      70,    93,    55,    80,    85,    96,    97,     5,    82,    68,
      71,    82,    13,    15,    16,    17,    81,    19,    55,    55,
     100,   101,    84,    85,    32,    69,    59,    68,    82,    22,
      48,    70,   108,   109,   110,   111,   112,   113,   114,   115,
     117,   117,     6,    83,    14,    14,    14,    12,    55,    36,
      37,    38,    39,    40,    41,   102,    68,    71,    68,    71,
      70,    55,   117,    97,   108,    70,   108,   117,    20,    21,
      22,    24,    25,    26,    27,    52,    53,    54,    59,    60,
      61,     7,     8,    86,    79,    70,    70,    22,    23,    42,
      44,    45,    47,   103,   104,   105,   101,    85,    94,   117,
      75,    71,   108,   108,    25,    26,    27,    22,    23,    70,
     117,   117,   117,   117,   117,   117,   117,   117,    84,   108,
       9,    87,    18,    57,    57,    23,    43,    56,    57,   106,
      43,   105,    68,    71,    71,    70,   117,   117,    23,   116,
     117,    20,     7,    49,    90,   108,    71,    71,    46,   117,
     116,    20,    68,    71,   117,    88,    89,   117,   117,    50,
      91,    80,    71,   117,   117,    68,    10,    11,   117,    70,
      89,    55,    71
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      75,    76,    76,    77,    77,    77,    78,    79,    79,    79,
      79,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    87,    88,    88,    89,    89,    89,    90,    90,    91,
      91,    92,    93,    93,    94,    94,    95,    96,    96,    97,
      98,    99,   100,   100,   101,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   119,   119,   120,   120
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     1,     1,     2,     2,
      10,     1,     3,     1,     3,     2,     1,     1,     2,     3,
       6,     1,     0,     1,     2,     2,     2,     1,     1,     1,
       0,     2,     0,     3,     1,     3,     1,     3,     0,     2,
       0,     3,     1,     3,     1,     2,     2,     0,     2,     0,
       2,     8,     0,     3,     1,     3,     5,     1,     3,     3,
       4,     6,     1,     3,     3,     1,     4,     4,     1,     1,
       1,     0,     1,     1,     2,     2,     1,     2,     1,     2,
       7,     1,     1,     2,     3,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     5,     6,     5,     6,     3,     4,     3,     4,     4,
       1,     3,     1,     3,     3,     3,     3,     2,     3,     1,
       1,     3,     1,     1,     1,     1,     3,     4,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = TOKEN_YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == TOKEN_YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use TOKEN_YYerror or TOKEN_YYUNDEF. */
#define YYERRCODE TOKEN_YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = TOKEN_YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == TOKEN_YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= TOKEN_YYEOF)
    {
      yychar = TOKEN_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == TOKEN_YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = TOKEN_YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = TOKEN_YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* query: query sql_statement  */
#line 79 "src/sql.y"
                                              { /* ignore */ }
#line 1375 "build/sql.tab.cpp"
    break;

  case 4: /* sql_statement: select_statement ';'  */
#line 83 "src/sql.y"
                          {(yyvsp[-1].select_statement_node)->print_select();}
#line 1381 "build/sql.tab.cpp"
    break;

  case 5: /* sql_statement: insert_statement ';'  */
#line 84 "src/sql.y"
                           {(yyvsp[-1].insert)->print_insert();}
#line 1387 "build/sql.tab.cpp"
    break;

  case 8: /* sql_statement: create_statement ';'  */
#line 87 "src/sql.y"
                           {(yyvsp[-1].create_tbl)->print_table();}
#line 1393 "build/sql.tab.cpp"
    break;

  case 9: /* sql_statement: drop_table ';'  */
#line 88 "src/sql.y"
                     {(yyvsp[-1].ast_node)->print_ast(0);}
#line 1399 "build/sql.tab.cpp"
    break;

  case 10: /* select_statement: SELECT select_list FROM table_reference_list where_clause_opt group_by_clause_opt having_clause_opt order_by_clause_opt limit_clause_opt offset_clause_opt  */
#line 94 "src/sql.y"
                                                                {
            /*phase 1*/
            select_node* select = new select_node();
            select->select_list.reset((yyvsp[-8].ast_node));
            select->table_reference_list.reset((yyvsp[-6].table_ref_list));
            (yyval.select_statement_node) = select;
        }
#line 1411 "build/sql.tab.cpp"
    break;

  case 11: /* select_list: select_item  */
#line 104 "src/sql.y"
                      {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        }
#line 1419 "build/sql.tab.cpp"
    break;

  case 12: /* select_list: select_list ',' select_item  */
#line 107 "src/sql.y"
                                      {
            AST* last = (yyvsp[-2].ast_node);
            while (last->ptr_sibling != nullptr) {
                last = last->ptr_sibling;
            }
            last->ptr_sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-2].ast_node);
        }
#line 1432 "build/sql.tab.cpp"
    break;

  case 13: /* select_item: expression  */
#line 118 "src/sql.y"
                     {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        }
#line 1440 "build/sql.tab.cpp"
    break;

  case 16: /* table_reference_list: table_reference  */
#line 126 "src/sql.y"
                      {(yyval.table_ref_list) = (yyvsp[0].table_ref_list);}
#line 1446 "build/sql.tab.cpp"
    break;

  case 17: /* table_reference: table_name  */
#line 135 "src/sql.y"
                 {
        from_clause* tbl_name = new from_clause();
        tbl_name->first_table.reset((yyvsp[0].ast_node));
        (yyval.table_ref_list) = tbl_name ;
    }
#line 1456 "build/sql.tab.cpp"
    break;

  case 18: /* table_reference: table_name IDENTIFIER  */
#line 140 "src/sql.y"
                            {}
#line 1462 "build/sql.tab.cpp"
    break;

  case 19: /* table_reference: table_name AS IDENTIFIER  */
#line 141 "src/sql.y"
                               {}
#line 1468 "build/sql.tab.cpp"
    break;

  case 20: /* table_reference: table_reference join_type JOIN table_reference ON search_condition  */
#line 142 "src/sql.y"
                                                                         {}
#line 1474 "build/sql.tab.cpp"
    break;

  case 21: /* table_name: IDENTIFIER  */
#line 146 "src/sql.y"
                 { 
        (yyval.ast_node) = new AST(std::string((yyvsp[0].str_val))) ;
    }
#line 1482 "build/sql.tab.cpp"
    break;

  case 34: /* column_reference_list: column_reference  */
#line 174 "src/sql.y"
                       { (yyval.ast_node) = (yyvsp[0].ast_node);}
#line 1488 "build/sql.tab.cpp"
    break;

  case 35: /* column_reference_list: column_reference_list ',' column_reference  */
#line 175 "src/sql.y"
                                                 {
        AST* last = (yyvsp[-2].ast_node);
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = (yyvsp[0].ast_node);
        (yyval.ast_node) = (yyvsp[-2].ast_node);
    }
#line 1501 "build/sql.tab.cpp"
    break;

  case 36: /* column_reference: IDENTIFIER  */
#line 186 "src/sql.y"
                 {
        (yyval.ast_node) = new AST(std::string((yyvsp[0].str_val)));
    }
#line 1509 "build/sql.tab.cpp"
    break;

  case 37: /* column_reference: table_name '.' IDENTIFIER  */
#line 189 "src/sql.y"
                                {

    }
#line 1517 "build/sql.tab.cpp"
    break;

  case 51: /* insert_statement: INSERT INTO table_name insert_columns_clause VALUES '(' insert_values_list ')'  */
#line 225 "src/sql.y"
                                                                                     {
        insert_stmt* insert_instance = new insert_stmt();
        insert_instance->table_name.reset((yyvsp[-5].ast_node));
        insert_instance->columns_to_insert = (yyvsp[-4].ast_node) ;
        insert_instance->values = (yyvsp[-1].ast_node);
        (yyval.insert) = insert_instance;
    }
#line 1529 "build/sql.tab.cpp"
    break;

  case 52: /* insert_columns_clause: %empty  */
#line 235 "src/sql.y"
                  { (yyval.ast_node) = nullptr;}
#line 1535 "build/sql.tab.cpp"
    break;

  case 53: /* insert_columns_clause: '(' column_reference_list ')'  */
#line 236 "src/sql.y"
                                    {
        (yyval.ast_node) = (yyvsp[-1].ast_node);
    }
#line 1543 "build/sql.tab.cpp"
    break;

  case 54: /* insert_values_list: expression  */
#line 242 "src/sql.y"
                 { (yyval.ast_node) = (yyvsp[0].ast_node) ;}
#line 1549 "build/sql.tab.cpp"
    break;

  case 55: /* insert_values_list: insert_values_list ',' expression  */
#line 243 "src/sql.y"
                                        {
        AST* last = (yyvsp[-2].ast_node);
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = (yyvsp[0].ast_node);
        (yyval.ast_node) = (yyvsp[-2].ast_node);
    }
#line 1562 "build/sql.tab.cpp"
    break;

  case 56: /* update_statement: UPDATE table_name SET update_list where_clause_opt  */
#line 255 "src/sql.y"
                                                         {
        
    }
#line 1570 "build/sql.tab.cpp"
    break;

  case 57: /* update_list: update_item  */
#line 261 "src/sql.y"
                  {

    }
#line 1578 "build/sql.tab.cpp"
    break;

  case 58: /* update_list: update_list ',' update_item  */
#line 264 "src/sql.y"
                                  {

    }
#line 1586 "build/sql.tab.cpp"
    break;

  case 59: /* update_item: column_reference '=' expression  */
#line 270 "src/sql.y"
                                      {

    }
#line 1594 "build/sql.tab.cpp"
    break;

  case 60: /* delete_statement: DELETE FROM table_name where_clause_opt  */
#line 277 "src/sql.y"
                                              {

    }
#line 1602 "build/sql.tab.cpp"
    break;

  case 61: /* create_statement: CREATE TABLE table_name '(' column_definition_list ')'  */
#line 284 "src/sql.y"
                                                             {
        create_table* table = new create_table();
        table->table_name.reset((yyvsp[-3].ast_node));
        table->columns_definitions=(yyvsp[-1].colmn_def);
        /*extra expilicit table constraints*/
        (yyval.create_tbl) = table;
    }
#line 1614 "build/sql.tab.cpp"
    break;

  case 62: /* column_definition_list: column_definition  */
#line 294 "src/sql.y"
                        { (yyval.colmn_def) = (yyvsp[0].colmn_def);}
#line 1620 "build/sql.tab.cpp"
    break;

  case 63: /* column_definition_list: column_definition_list ',' column_definition  */
#line 295 "src/sql.y"
                                                  {
        AST* last = (AST*)(yyvsp[-2].colmn_def);
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = (AST*)(yyvsp[0].colmn_def);
        (yyval.colmn_def) = (yyvsp[-2].colmn_def); 
    }
#line 1633 "build/sql.tab.cpp"
    break;

  case 64: /* column_definition: IDENTIFIER data_type column_constraint_list_opt  */
#line 306 "src/sql.y"
                                                      {
        column_definition* clmn_def = new column_definition();
        clmn_def->Column = std::string((yyvsp[-2].str_val));
        clmn_def->Type.reset((yyvsp[-1].dtype));
        clmn_def->constraints.reset((yyvsp[0].ast_node));
        (yyval.colmn_def) = clmn_def;
    }
#line 1645 "build/sql.tab.cpp"
    break;

  case 65: /* data_type: INT  */
#line 316 "src/sql.y"
            {
        (yyval.dtype) = new inttype();
    }
#line 1653 "build/sql.tab.cpp"
    break;

  case 66: /* data_type: CHAR '(' INTEGER_LITERAL ')'  */
#line 319 "src/sql.y"
                                   {
        // $$ = new 
    }
#line 1661 "build/sql.tab.cpp"
    break;

  case 67: /* data_type: VARCHAR '(' INTEGER_LITERAL ')'  */
#line 322 "src/sql.y"
                                     {
        (yyval.dtype) = new varchar((yyvsp[-1].int_val));
    }
#line 1669 "build/sql.tab.cpp"
    break;

  case 68: /* data_type: NUMBER  */
#line 325 "src/sql.y"
             {

    }
#line 1677 "build/sql.tab.cpp"
    break;

  case 69: /* data_type: DATE  */
#line 328 "src/sql.y"
           {

    }
#line 1685 "build/sql.tab.cpp"
    break;

  case 70: /* data_type: TEXT  */
#line 331 "src/sql.y"
           {

    }
#line 1693 "build/sql.tab.cpp"
    break;

  case 71: /* column_constraint_list_opt: %empty  */
#line 337 "src/sql.y"
                  { (yyval.ast_node) = nullptr;}
#line 1699 "build/sql.tab.cpp"
    break;

  case 72: /* column_constraint_list_opt: column_constraint_list  */
#line 338 "src/sql.y"
                             { (yyval.ast_node) = (yyvsp[0].ast_node);}
#line 1705 "build/sql.tab.cpp"
    break;

  case 73: /* column_constraint_list: column_constraint  */
#line 342 "src/sql.y"
                        { (yyval.ast_node) = (yyvsp[0].ast_node);}
#line 1711 "build/sql.tab.cpp"
    break;

  case 74: /* column_constraint_list: column_constraint_list column_constraint  */
#line 343 "src/sql.y"
                                               {
        AST* last = (yyvsp[-1].ast_node);
        while (last->ptr_sibling != nullptr) {
            last = last->ptr_sibling;
        }
        last->ptr_sibling = (yyvsp[0].ast_node);
        (yyval.ast_node) = (yyvsp[-1].ast_node); 
    }
#line 1724 "build/sql.tab.cpp"
    break;

  case 75: /* column_constraint: NOT SQLNULL  */
#line 354 "src/sql.y"
                  {
        (yyval.ast_node) = new AST("NOT NULL");
    }
#line 1732 "build/sql.tab.cpp"
    break;

  case 76: /* column_constraint: SQLNULL  */
#line 357 "src/sql.y"
              {
        (yyval.ast_node) = new AST("NULL");
    }
#line 1740 "build/sql.tab.cpp"
    break;

  case 77: /* column_constraint: PRIMARY KEY  */
#line 360 "src/sql.y"
                  {
        (yyval.ast_node) = new AST("PRIMARY KEY");
    }
#line 1748 "build/sql.tab.cpp"
    break;

  case 78: /* column_constraint: UNIQUE  */
#line 363 "src/sql.y"
             {
        (yyval.ast_node) = new AST("UNIQUE");
    }
#line 1756 "build/sql.tab.cpp"
    break;

  case 79: /* column_constraint: DEFAULT default_value  */
#line 366 "src/sql.y"
                            {
        AST* type = new AST("DEFAULT");
        type->ptr_sibling = (AST*)(yyvsp[0].dtype);
        (yyval.ast_node) = type;
    }
#line 1766 "build/sql.tab.cpp"
    break;

  case 80: /* column_constraint: FOREIGN KEY REFERENCES table_name '(' IDENTIFIER ')'  */
#line 371 "src/sql.y"
                                                           {
        AST* type = new AST("FOREIGN KEY");
        type->ptr_children = (yyvsp[-3].ast_node);
        type->ptr_children->ptr_sibling = new AST(std::string((yyvsp[-1].str_val))) ;
        (yyval.ast_node) = type;
    }
#line 1777 "build/sql.tab.cpp"
    break;

  case 81: /* default_value: INTEGER_LITERAL  */
#line 380 "src/sql.y"
                      {
        datatype* data = new inttype();
        ((inttype*)data)->value = (yyvsp[0].int_val);
        (yyval.dtype) = data;
    }
#line 1787 "build/sql.tab.cpp"
    break;

  case 82: /* default_value: STRING_LITERAL  */
#line 386 "src/sql.y"
                      { 
        datatype* data = new varchar(10);
        ((varchar*)data)->value = std::string((yyvsp[0].str_val));
        (yyval.dtype) = data;
    }
#line 1797 "build/sql.tab.cpp"
    break;

  case 83: /* drop_table: DROP table_name  */
#line 396 "src/sql.y"
                      {
        AST* drop = new AST("DROP TABLE");
        drop->ptr_children = (yyvsp[0].ast_node);
        (yyval.ast_node) = drop;
    }
#line 1807 "build/sql.tab.cpp"
    break;

  case 112: /* expression: term  */
#line 461 "src/sql.y"
           { (yyval.ast_node) = (yyvsp[0].ast_node);}
#line 1813 "build/sql.tab.cpp"
    break;

  case 113: /* expression: expression '+' expression  */
#line 462 "src/sql.y"
                                {}
#line 1819 "build/sql.tab.cpp"
    break;

  case 114: /* expression: expression '-' expression  */
#line 463 "src/sql.y"
                                {}
#line 1825 "build/sql.tab.cpp"
    break;

  case 115: /* expression: expression '*' expression  */
#line 464 "src/sql.y"
                                {}
#line 1831 "build/sql.tab.cpp"
    break;

  case 116: /* expression: expression '/' expression  */
#line 465 "src/sql.y"
                                {}
#line 1837 "build/sql.tab.cpp"
    break;

  case 117: /* expression: '-' expression  */
#line 466 "src/sql.y"
                                  {}
#line 1843 "build/sql.tab.cpp"
    break;

  case 118: /* expression: '(' expression ')'  */
#line 467 "src/sql.y"
                         {}
#line 1849 "build/sql.tab.cpp"
    break;

  case 119: /* expression: function_call  */
#line 468 "src/sql.y"
                    {}
#line 1855 "build/sql.tab.cpp"
    break;

  case 120: /* term: IDENTIFIER  */
#line 472 "src/sql.y"
                   {
        (yyval.ast_node) = new AST(std::string((yyvsp[0].str_val))) ;;
    }
#line 1863 "build/sql.tab.cpp"
    break;

  case 121: /* term: table_name '.' IDENTIFIER  */
#line 475 "src/sql.y"
                                {}
#line 1869 "build/sql.tab.cpp"
    break;

  case 122: /* term: INTEGER_LITERAL  */
#line 476 "src/sql.y"
                      {
        datatype* data = new inttype();
        ((inttype*)data)->value = (yyvsp[0].int_val);
        AST* intnode = new AST("INT");
        intnode->ptr_children = (AST*)data;
        (yyval.ast_node) = intnode;
    }
#line 1881 "build/sql.tab.cpp"
    break;

  case 123: /* term: FLOAT_LITERAL  */
#line 483 "src/sql.y"
                    {
        // $$ = new AST(std::to_string($1));
    }
#line 1889 "build/sql.tab.cpp"
    break;

  case 124: /* term: STRING_LITERAL  */
#line 486 "src/sql.y"
                     {
        datatype* data = new varchar(10);
        ((varchar*)data)->value = std::string((yyvsp[0].str_val));
        AST* strnode = new AST("STR");
        strnode->ptr_children = (AST*)data;
        (yyval.ast_node) = strnode;
    }
#line 1901 "build/sql.tab.cpp"
    break;

  case 125: /* term: '*'  */
#line 493 "src/sql.y"
         {
        (yyval.ast_node) = new AST("*") ;
    }
#line 1909 "build/sql.tab.cpp"
    break;

  case 126: /* function_call: IDENTIFIER '(' ')'  */
#line 499 "src/sql.y"
                         {}
#line 1915 "build/sql.tab.cpp"
    break;

  case 127: /* function_call: IDENTIFIER '(' function_arg_list ')'  */
#line 500 "src/sql.y"
                                           {}
#line 1921 "build/sql.tab.cpp"
    break;

  case 128: /* function_arg_list: expression  */
#line 504 "src/sql.y"
                 {}
#line 1927 "build/sql.tab.cpp"
    break;

  case 129: /* function_arg_list: function_arg_list ',' expression  */
#line 505 "src/sql.y"
                                       {}
#line 1933 "build/sql.tab.cpp"
    break;


#line 1937 "build/sql.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == TOKEN_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= TOKEN_YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == TOKEN_YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = TOKEN_YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != TOKEN_YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 508 "src/sql.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
