#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizator_sem.h"
#include "generator_assembly.h"

void initialize_symbol_table() {
    var_count = 0;
}

bool add_variable(char *name, VarType type) {
    if (var_count >= MAX_VARIABLES) {
        fprintf(stderr, "Error: Too many variables\n");
        return false;
    }
    symbol_table[var_count].name = strdup(name);
    symbol_table[var_count].type = type;
    var_count++;
    return true;
}

VarType get_variable_type(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].type;
        }
    }
    return TYPE_UNKNOWN;
}

void check_variable_usage(char *var_name) {
    if (get_variable_type(var_name) == TYPE_UNKNOWN) {
        fprintf(stderr, "Error: Variable '%s' not declared\n", var_name);
    }
}

