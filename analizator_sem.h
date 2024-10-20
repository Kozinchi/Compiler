#ifndef ANALIZATOR_SEM_H
#define ANALIZATOR_SEM_H
#include <stdbool.h>
#define MAX_VARIABLES 100

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_UNKNOWN
} VarType;

typedef struct {
    char *name;
    VarType type;
} Variable;

Variable symbol_table[MAX_VARIABLES];
int var_count;

void initialize_symbol_table();
bool add_variable(char *name, VarType type);
VarType get_variable_type(char *name);
void check_variable_usage(char *var_name);

#endif
