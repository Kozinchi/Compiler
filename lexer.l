%{

#include "parser.tab.h"
#include <string.h>

%}

%%

"="                 { return ASSIGNMENT; }
"=="                { return EQUAL; }
"!="                { return NOT_EQUAL; }
">"                 { return HIGHER_THAN; }
"<"                 { return LESS_THAN; }
">="                { return HIGHER_EQUAL; }
"<="                { return LESS_EQUAL; }
"!"                 { return NEGATION; }

"("                 { return LEFT_PAREN; }
")"                 { return RIGHT_PAREN; }
"{"                 { return LEFT_BRACE; }
"}"                 { return RIGHT_BRACE; }
"["                 { return LEFT_BRACKET; }
"]"                 { return RIGHT_BRACKET; }

"/"                 { return DIVISION; }
"+"                 { return ADDITION; }
"-"                 { return SUBTRACTION; }
"*"                 { return MULTIPLICATION; }

","                 { return COMMA; }

"++"                { return INCREMENT; }
"--"                { return DECREMENT; }

";"                 { return SEMICOLON; }

"int"               { return INT; }
"var"               { return VAR; }
"double"            { return DOUBLE; }
"string"            { return STRING; }

"if"                { return IF; }
"else"              { return ELSE; }
"for"               { return FOR; }

".p"                { return PRINT_FUNCTION; }
".m"                { return MATH_FUNCTION; }

[a-zA-Z_][a-zA-Z0-9_]*        { yylval.sval = strdup(yytext); return VARIABLE_NAME; }
\"[a-zA-Z_][a-zA-Z0-9_ ]*\"   { yylval.stringval = strdup(yytext); return STRINGV; }
[0-9]+                        { yylval.ival = atoi(yytext); return NUM; }
[0-9]+\.[0-9]+                { yylval.dval = atof(yytext); return DNUM; }

%%
