#include "analizator_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 100

VARIABLE variables[MAX_VARIABLES];

int varCount = 0;

int addVariable(const char *name, VAR_TYPE type, VALUE_TYPE value)
{
    if (varCount >= MAX_VARIABLES)
    {
        fprintf(stderr, "Error: Maximum variable limit reached.\n");
        return -1;
    }

    for (int i = 0; i < varCount; i++)
    {
        if (strcmp(variables[i].name, name) == 0)
        {
            fprintf(stderr, "Error: Variable '%s' already declared.\n", name);
            return -1;
        }
    }

    variables[varCount].name = strdup(name);
    variables[varCount].type = type;
    variables[varCount].valueStorage = value;
    varCount++;

    return 0;
}

VARIABLE *getVariable(const char *name)
{
    for (int i = 0; i < varCount; i++)
    {
        if (strcmp(variables[i].name, name) == 0)
        {
            return &variables[i];
        }
    }
    
    return NULL;
}

int checkTypes(VAR_TYPE expected, VAR_TYPE actual)
{
    if (expected != actual)
    {
        fprintf(stderr, "Type error: expected '%d', but got '%d'.\n", expected, actual);
        return -1;
    }
    
    return 0;
}

void freeVariables()
{
    for (int i = 0; i < varCount; i++)
    {
        free(variables[i].name);
    }
}

void performOperation(const char *var1Name, const char *var2Name, const char *op)
{
    VARIABLE *var1 = getVariable(var1Name);
    VARIABLE *var2 = getVariable(var2Name);
    
    if (!var1 || !var2)
    {
        fprintf(stderr, "Error: One or both variables not found.\n");
        return;
    }

    VALUE_TYPE result;
    
    VAR_TYPE resultType;

    resultType = (var1->type == doubleType || var2->type == doubleType) ? doubleType : intType;

    if (strcmp(op, "+") == 0)
    {
        result.doubleValue = (var1->type == intType ? var1->valueStorage.intValue : var1->valueStorage.doubleValue) +
                             (var2->type == intType ? var2->valueStorage.intValue : var2->valueStorage.doubleValue);
    }
    else if (strcmp(op, "-") == 0)
    {
        result.doubleValue = (var1->type == intType ? var1->valueStorage.intValue : var1->valueStorage.doubleValue) -
                             (var2->type == intType ? var2->valueStorage.intValue : var2->valueStorage.doubleValue);
    } 
    else if (strcmp(op, "*") == 0)
    {
        result.doubleValue = (var1->type == intType ? var1->valueStorage.intValue : var1->valueStorage.doubleValue) *
                             (var2->type == intType ? var2->valueStorage.intValue : var2->valueStorage.doubleValue);
    } 
    else if (strcmp(op, "/") == 0)
    {
        if ((var2->type == intType && var2->valueStorage.intValue == 0) || (var2->type == doubleType && var2->valueStorage.doubleValue == 0.0))
        {
            fprintf(stderr, "Error: Division by zero.\n");
            return;
        }
        result.doubleValue = (var1->type == intType ? var1->valueStorage.intValue : var1->valueStorage.doubleValue) /
                             (var2->type == intType ? var2->valueStorage.intValue : var2->valueStorage.doubleValue);
    } 
    else
    {
        fprintf(stderr, "Error: Unsupported operation '%s'.\n", op);
        return;
    }

    char resultVarName[100];
    
    snprintf(resultVarName, sizeof(resultVarName), "%s_%s_%s", var1Name, var2Name, op);

    VALUE_TYPE value;
    
    if (resultType == intType)
    {
        value.intValue = (int)result.doubleValue;
        addVariable(resultVarName, intType, value);
        printf("Result: %s %s %s = %d\n", var1Name, op, var2Name, value.intValue);
    }
    else
    {
        value.doubleValue = result.doubleValue;
        addVariable(resultVarName, doubleType, value);
        printf("Result: %s %s %s = %f\n", var1Name, op, var2Name, value.doubleValue);
    }
}
