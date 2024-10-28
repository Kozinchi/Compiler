#ifndef ASSEMBLY_GENERATOR_H
#define ASSEMBLY_GENERATOR_H
#include <stdio.h>

#include "analizator_sem.h"

void createSection(FILE *file, const char* sectionName);
void createStart(FILE *file);
void end(FILE *file);
void initializePrints(FILE *file);

void printEnd(STACK *stack);
void dumpFlow(FILE *file);

void assignMathToVariable(STACK *stack, const char *varName);
void assignWithTemp(STACK *stack, const char *name, const char *tempName, VAR_TYPE type);
void assignVariable(STACK *stack, const char *name, VAR_TYPE type, VALUE_TYPE value);
void assignTwoVariables(STACK *stack, const char *name, const char *assigningName, VAR_TYPE type);

void pushAddToCurrentFlowStack(STACK *mstack, STACK *currStack);
void pushSubtractToCurrentFlowStack(STACK *mstack, STACK *currStack);
void pushMultiplyToCurrentFlowStack(STACK *mstack, STACK *currStack);
void pushDivideToCurrentFlowStack(STACK *mstack, STACK *currStack);

void dumpStack(FILE *file, STACK *stack);
void dumpVariables(FILE *file, VARIABLE *variableTable);

#endif
