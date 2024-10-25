#include "generator_assembler.h"

void generateAssemblyCode(const char *operation, const char *var1Name, const char *var2Name, const char *resultVarName, VALUE_TYPE result, VAR_TYPE resultType)
{
    FILE *outputFile = fopen("output.asm", "a"); 
    if (!outputFile)
    {
        perror("Error opening file");
        return;
    }

    fprintf(outputFile, ";; Generating assembly code for %s %s %s\n", var1Name, operation, var2Name);
    
    if (resultType == intType)
    {
        fprintf(outputFile, "mov eax, %s\n", var1Name);
        if (strcmp(operation, "+") == 0)
        {
            fprintf(outputFile, "add eax, %s\n", var2Name);
        } 
        else if (strcmp(operation, "-") == 0)
        {
            fprintf(outputFile, "sub eax, %s\n", var2Name);
        } 
        else if (strcmp(operation, "*") == 0)
        {
            fprintf(outputFile, "imul eax, %s\n", var2Name);
        } 
        else if (strcmp(operation, "/") == 0)
        {
            fprintf(outputFile, "xor edx, edx\n");
            fprintf(outputFile, "div %s\n", var2Name);
        } 
        else
        {
            fprintf(stderr, "Error: Unsupported operation '%s'.\n", operation);
        }
        
        fprintf(outputFile, "mov %s, eax\n", resultVarName);
    } 
    else if (resultType == doubleType)
    {
        fprintf(outputFile, "movsd xmm0, [%s]\n", var1Name);
        if (strcmp(operation, "+") == 0)
        {
            fprintf(outputFile, "addsd xmm0, [%s]\n", var2Name);
        } 
        else if (strcmp(operation, "-") == 0)
        {
            fprintf(outputFile, "subsd xmm0, [%s]\n", var2Name);
        } 
        else if (strcmp(operation, "*") == 0)
        {
            fprintf(outputFile, "mulsd xmm0, [%s]\n", var2Name);
        } 
        else if (strcmp(operation, "/") == 0)
        {
            fprintf(outputFile, "divsd xmm0, [%s]\n", var2Name);
        } 
        else
        {
            fprintf(stderr, "Error: Unsupported operation '%s'.\n", operation);
        }
        fprintf(outputFile, "movsd [%s], xmm0\n", resultVarName);
    } 
    else
    {
        fprintf(stderr, "Error: Unsupported result type for assembly generation.\n");
    }

    fclose(outputFile);
}

void initAssembler()
{
    FILE *outputFile = fopen("output.asm", "w"); 
    if (!outputFile)
    {
        perror("Error opening file");
        return;
    }

    fprintf(outputFile, ";; Assembly code generated by the custom compiler\n");
    fprintf(outputFile, "section .data\n");
    fprintf(outputFile, "section .text\n");
    fprintf(outputFile, "global _start\n");

    fclose(outputFile);
}

void freeAssembler()
{
    if (remove("output.asm") == 0)
    {
        printf("Output file removed successfully.\n");
    }
    else
    {
        perror("Error removing output file");
    }
}

