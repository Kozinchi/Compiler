#ifndef ANALIZATOR_SEM_H
#define ANALIZATOR_SEM_H

typedef enum {
    intType,
    varType,
    doubleType,
    stringType,
    undefinedType
} VAR_TYPE;

typedef enum {
    intArray,
    doubleArray,
    stringArray,
    undefinedArray
} ARRAY_TYPE;

typedef enum {
    equality,
    higherEquality,
    lessEquality,
    higher,
    less,
    different,
} CONDITION_TYPE;

typedef enum {
    additionExp,
    subtractionExp,
    multiplicationExp,
    divisionExp,
    undefinedExp
} EXPRESSION_TYPE;

typedef enum {
    finc,
    fdec
} FOR_INC_TYPE;

typedef enum {
    fbigger,
    fsmaller,
    fhigherequality,
    fsmallerequality
} FOR_CONDITION_TYPE;

typedef union {
    int intValue;
    double doubleValue;
    char* stringValue;
} VALUE_TYPE;

typedef union {
    int* integerArray;
    double* doubleArray;
    char** stringArray;
} ARRAY_VALUE;

typedef struct {
    char *name;
    VAR_TYPE type;
    VALUE_TYPE valuestorage;
} VARIABLE;

typedef struct {
    char *name;
    ARRAY_TYPE arrayType;
    ARRAY_VALUE arrayValue;
    int arraySize;
} ARRAY_VARIABLE;

typedef struct {
    char *name;
    char *accessName;
    int id;
    VAR_TYPE type;
    VALUE_TYPE valuestorage;
} PRIVATE_VARIABLE;
#endif
