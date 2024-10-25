%{
#include "analizator_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex(void);
%}

%token ASSIGNMENT EQUAL NOT_EQUAL HIGHER_THAN LESS_THAN
%token SEMICOLON IF ELSE FOR PRINT_FUNCTION
%token VARIABLE_NAME NUM DNUM STRINGV
%token ADDITION SUBTRACTION MULTIPLICATION DIVISION
%type <ival> expression
%type <sval> statement // Dodaj tę linijkę, aby określić typ dla statement

%%

// Główna struktura programu
program:
    program statement
    | /* empty */
    ;

// Instrukcje
statement:
    VARIABLE_NAME ASSIGNMENT expression SEMICOLON
    {
        add_variable($1, TYPE_INT); // Przykład: zakładamy, że to int
    }
    | IF '(' expression ')' statement ELSE statement
    | FOR '(' statement expression SEMICOLON statement ')' statement
    | PRINT_FUNCTION '(' expression ')' SEMICOLON
    ;

// Wyrażenia
expression:
    NUM { $$ = $1; }
    | VARIABLE_NAME
    {
        check_variable_usage($1);
        $$ = get_variable_type($1);
    }
    | expression ADDITION expression { $$ = $1 + $3; }
    | expression SUBTRACTION expression { $$ = $1 - $3; }
    | expression MULTIPLICATION expression { $$ = $1 * $3; }
    | expression DIVISION expression { $$ = $1 / $3; }
    | '(' expression ')' { $$ = $2; }
    | STRINGV { $$ = 0; }
    | DNUM { $$ = (int)$1; }
    ;

// Błąd
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    initialize_symbol_table();
    return yyparse();
}
