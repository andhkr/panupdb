%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "include/ast.hpp"
#include "include/datatypes.hpp"
#include "sql.tab.hpp"        /* bison token/union definitions */

#define YY_DECL int yylex (void)
%}

%option noyywrap
%option nounput noinput batch
%option case-insensitive

%%
 /* ---------- keywords ---------------------------------------------------- */
"SELECT"         { return TOKEN_SELECT; }
"FROM"           { return TOKEN_FROM; }
"WHERE"          { return TOKEN_WHERE; }
"GROUP"          { return TOKEN_GROUP; }
"BY"             { return TOKEN_BY; }
"HAVING"         { return TOKEN_HAVING; }
"ORDER"          { return TOKEN_ORDER; }
"ASC"            { return TOKEN_ASC; }
"DESC"           { return TOKEN_DESC; }
"JOIN"           { return TOKEN_JOIN; }
"INNER"          { return TOKEN_INNER; }
"OUTER"          { return TOKEN_OUTER; }
"LEFT"           { return TOKEN_LEFT; }
"RIGHT"          { return TOKEN_RIGHT; }
"FULL"           { return TOKEN_FULL; }
"ON"             { return TOKEN_ON; }
"AS"             { return TOKEN_AS; }
"AND"            { return TOKEN_AND; }
"OR"             { return TOKEN_OR; }
"NOT"            { return TOKEN_NOT; }
"NULL"           { return TOKEN_SQLNULL; }
"IS"             { return TOKEN_IS; }
"IN"             { return TOKEN_IN; }
"LIKE"           { return TOKEN_LIKE; }
"BETWEEN"        { return TOKEN_BETWEEN; }
"CREATE"         { return TOKEN_CREATE; }
"DATABASE"       { return TOKEN_DATABASE; }
"CREATEDB"       { return TOKEN_CREATEDB; }
"TABLE"          { return TOKEN_TABLE; }
"INSERT"         { return TOKEN_INSERT; }
"INTO"           { return TOKEN_INTO; }
"VALUES"         { return TOKEN_VALUES; }
"UPDATE"         { return TOKEN_UPDATE; }
"SET"            { return TOKEN_SET; }
"DELETE"         { return TOKEN_DELETE; }
"INT"            { return TOKEN_INT; }
"CHAR"           { return TOKEN_CHAR; }
"VARCHAR"        { return TOKEN_VARCHAR; }
"NUMBER"         { return TOKEN_NUMBER; }
"DATE"           { return TOKEN_DATE; }
"TEXT"           { return TOKEN_TEXT; }
"PRIMARY"        { return TOKEN_PRIMARY; }
"KEY"            { return TOKEN_KEY; }
"UNIQUE"         { return TOKEN_UNIQUE; }
"DEFAULT"        { return TOKEN_DEFAULT; }
"REFERENCES"     { return TOKEN_REFERENCES; }
"EXISTS"         { return TOKEN_EXISTS; }
"DROP"           { return TOKEN_DROP; }

 /* ---------- operators / punctuation ------------------------------------- */
"<="             { return TOKEN_LE; }
">="             { return TOKEN_GE; }
"<>"             { return TOKEN_NE; }
"!="             { return TOKEN_NE; }

 /* single-character tokens */  
[=<>+\-*/(),.;]   { return yytext[0]; }

 /* ---------- identifiers & literals -------------------------------------- */
[A-Za-z_][A-Za-z0-9_]* {
    yylval.str_val = strdup (yytext);
    return TOKEN_IDENTIFIER;
}

'([^']|'')*' {                         /* SQL string literal, '' escapes */
    yylval.str_val = strdup (yytext);
    return TOKEN_STRING_LITERAL;
}

[0-9]+ {
    yylval.int_val = std::atoi (yytext);
    return TOKEN_INTEGER_LITERAL;
}

([0-9]+"."[0-9]*)|("."[0-9]+) {
    yylval.float_val = std::atof (yytext);
    return TOKEN_FLOAT_LITERAL;
}

 /* ---------- skip whitespace & comments ---------------------------------- */
[ \t\r\n]+        ;                    /* ignore whitespace */

. { std::fprintf (stderr, "unknown char: %s\n", yytext); }

%%

