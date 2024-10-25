#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

typedef enum
{
    intType,
    varType,
    doubleType,
    stringType,
    undefinedType
} VAR_TYPE;

typedef enum
{
    additionExp,
    subtractionExp,
    multiplicationExp,
    divisionExp,
    undefinedExp
} EXPRESSION_TYPE;

typedef union
{
    int intValue;
    double doubleValue;
    char* stringValue;
} VALUE_TYPE;

typedef struct
{
    char *name;
    VAR_TYPE type;
    VALUE_TYPE valueStorage;
} VARIABLE;

typedef struct
{
    char instruction[256];
} ASSEMBLY_INSTRUCTION;

typedef struct StackNode
{
    ASSEMBLY_INSTRUCTION instruction;
    struct StackNode *next;
} STACK_NODE;

typedef struct
{
    STACK_NODE *top;
} STACK;

typedef struct
{
    EXPRESSION_TYPE type;
    int isAlreadyComputed;
    const char *varName;
} MATH_STACK_INSIDE;

typedef struct MathStackNode
{
    MATH_STACK_INSIDE data;
    struct MathStackNode *next;
} MATH_STACK_NODE;

typedef struct
{
    MATH_STACK_NODE *top;
} MATH_STACK;

#endif
