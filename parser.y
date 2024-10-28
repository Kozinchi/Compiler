%{

#include "analizator_sem.h"
#include "generator_assembly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);

int yylex(void);

extern FILE *yyin;

%}

%union
{
    double dval;
    int ival;
    char* sval;
    char* stringval;
}

%left ADDITION SUBTRACTION
%left MULTIPLICATION DIVISION

%token <ival> NUM
%token <dval> DNUM
%token <sval> VARIABLE_NAME
%token <stringval> STRINGV

%token ASSIGNMENT EQUAL NOT_EQUAL HIGHER_THAN LESS_THAN HIGHER_EQUAL LESS_EQUAL NEGATION
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token DIVISION ADDITION SUBTRACTION MULTIPLICATION
%token COMMA INCREMENT DECREMENT SEMICOLON
%token INT VAR DOUBLE STRING
%token IF ELSE FOR
%token PRINT_FUNCTION MATH_FUNCTION

%type <dval> expression

%% 	

program:
    | program statement
    ;

statement:
    VARIABLE_NAME ASSIGNMENT expression SEMICOLON
    {
        VALUE_TYPE value;
        
        if ((int)$3 == $3)
        {
            value.intValue = (int)$3;
            addVariable($1, intType, value);
            printf("Variable added: %s = %d\n", $1, value.intValue);
        }
        else
        {
            value.doubleValue = $3;
            addVariable($1, doubleType, value);
            printf("Variable added: %s = %f\n", $1, value.doubleValue);
        }
    }
    | IF LEFT_PAREN expression RIGHT_PAREN statement
    ;

    
expression:
    expression ADDITION expression { $$ = $1 + $3; }
    | expression SUBTRACTION expression { $$ = $1 - $3; }
    | expression MULTIPLICATION expression { $$ = $1 * $3; }
    | expression DIVISION expression
    {
        if ($3 == 0)
        {
            printf("Error: Divided by zero.\n");
            $$ = 0;
        }
        else
        {
            $$ = $1 / $3;
        }
    }
    | NUM { $$ = $1; }
    | DNUM { $$ = $1; }
    | VARIABLE_NAME
    {
        VARIABLE *var = getVariable($1);
        
        if (var)
        {
            if (var->type == intType)
            {
                $$ = var->valueStorage.intValue;
            }
            else
            {
                $$ = var->valueStorage.doubleValue;
            }
        }
        else
        {
            printf("Error: Variable '%s' did not get declared.\n", $1);
            $$ = 0;
        }
    }
    | LEFT_PAREN expression RIGHT_PAREN { $$ = $2; }
    ;

%% 

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Using: %s <plik_wejsciowy>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    
    if (!yyin)
    {
        perror("Error while opening source file");
        return 1;
    }

    yyparse();
    fclose(yyin);
    freeVariables();
    return 0;
}
