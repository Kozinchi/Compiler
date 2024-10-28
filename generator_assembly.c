#include "generator_assembly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createSection(FILE *file, const char* sectionName)
{
    fprintf(file, "section .%s\n", sectionName);
}

void createStart(FILE *file)
{
    fprintf(file, "global _start\n");
    fprintf(file, "_start:\n");
}

void end(FILE *file)
{
    fprintf(file, "mov eax, 1\n");
    fprintf(file, "int 0x80\n");
}

void pushAddToCurrentFlowStack(STACK *mstack, STACK *currStack)
{
    ASSEMBLY_INSTRUCTION instr;
    strcpy(instr.instruction, "ADD eax, ebx\n");
    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = currStack->top;
    currStack->top = newNode;
}

void pushSubtractToCurrentFlowStack(STACK *mstack, STACK *currStack)
{
    ASSEMBLY_INSTRUCTION instr;
    strcpy(instr.instruction, "SUB eax, ebx\n");
    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = currStack->top;
    currStack->top = newNode;
}

void pushMultiplyToCurrentFlowStack(STACK *mstack, STACK *currStack)
{
    ASSEMBLY_INSTRUCTION instr;
    strcpy(instr.instruction, "MUL ebx\n");
    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = currStack->top;
    currStack->top = newNode;
}

void pushDivideToCurrentFlowStack(STACK *mstack, STACK *currStack)
{
    ASSEMBLY_INSTRUCTION instr;
    strcpy(instr.instruction, "DIV ebx\n");
    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = currStack->top;
    currStack->top = newNode;
}

void assignVariable(STACK *stack, const char *name, VAR_TYPE type, VALUE_TYPE value)
{
    ASSEMBLY_INSTRUCTION instr;
    
    if (type == intType)
    {
        sprintf(instr.instruction, "mov [%s], %d\n", name, value.intValue);
    }
    else if (type == doubleType)
    {
        sprintf(instr.instruction, "mov [%s], %f\n", name, value.doubleValue);
    }
    
    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = stack->top;
    stack->top = newNode;
}

void dumpStack(FILE *file, STACK *stack)
{
    STACK_NODE *current = stack->top;
    
    while (current != NULL)
    {
        fprintf(file, "%s", current->instruction.instruction);
        current = current->next;
    }
}

void assignMathToVariable(STACK *stack, const char *varName)
{
    ASSEMBLY_INSTRUCTION instr;
    sprintf(instr.instruction, "mov [%s], eax\n", varName);

    STACK_NODE *newNode = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    newNode->instruction = instr;
    newNode->next = stack->top;
    stack->top = newNode;
}
