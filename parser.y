%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizator_sem.h"
#include "generator_assembly.h"

void yyerror(const char *s);
int yylex(void);

%}

%union {
    double dval;
    int ival;
    char* sval;
    char* stringval;
}

%token <ival> NUM
%token <dval> DNUM
%token <sval> VARIABLE_NAME
%token <stringval> STRINGV
%token ASSIGNMENT EQUAL NOT_EQUAL HIGHER_THAN LESS_THAN HIGHER_EQUAL LESS_EQUAL NEGATION
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token DIVISION ADDITION SUBTRACTION MULTIPLICATION INCREMENT DECREMENT
%token SEMICOLON IF ELSE FOR
%token INT DOUBLE STRING VAR
%token COMMA PRINT_FUNCTION MATH_FUNCTION

%type <dval> expression
%type <ival> statement

%% 	

program:
    | program statement
    ;

statement:
    VARIABLE_NAME ASSIGNMENT expression SEMICOLON
    {
        VALUE_TYPE value;
        if ($3.dval != 0.0) {
            value.doubleValue = $3.dval;
            addVariable($1, doubleType, value);
            printf("Dodano zmienną: %s = %f\n", $1, value.doubleValue);
        } else {
            value.intValue = $3.ival;
            addVariable($1, intType, value);
            printf("Dodano zmienną: %s = %d\n", $1, value.intValue);
        }
    }
    | IF LEFT_PAREN expression RIGHT_PAREN statement {
        if ($3.ival) {
            printf("Warunek prawdziwy: %d\n", $3.ival);
        }
    }
    ;

expression:
    expression ADDITION expression { 
        $$ = $1 + $3; 
    }
    | expression SUBTRACTION expression { 
        $$ = $1 - $3; 
    }
    | expression MULTIPLICATION expression { 
        $$ = $1 * $3; 
    }
    | expression DIVISION expression { 
        if ($3 == 0) {
            printf("Błąd: Dzielenie przez zero.\n");
            $$ = 0;
        } else {
            $$ = $1 / $3; 
        }
    }
    | NUM { 
        $$ = $1; 
    }
    | DNUM { 
        $$ = $1; 
    }
    | VARIABLE_NAME {
        VARIABLE *var = getVariable($1);
        if (var) {
            if (var->type == intType) {
                $$ = var->valueStorage.intValue;
            } else {
                $$ = var->valueStorage.doubleValue;
            }
        } else {
            printf("Błąd: Zmienna '%s' nie została zadeklarowana.\n", $1);
            $$ = 0;
        }
    }
    | LEFT_PAREN expression RIGHT_PAREN { 
        $$ = $2; 
    }
    ;

%% 

void yyerror(const char *s) {
    fprintf(stderr, "Błąd: %s\n", s);
}

int main(void) {
    printf("Wprowadź dane (użyj 'exit' aby zakończyć):\n");
    yyparse();
    freeVariables();
    return 0;
}

