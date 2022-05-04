#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "user/config.h"
#include "user/program.h"
#include "config_flags.h"
#include "errors.h"
#include "colors.h"
#include "tokens.h"
#include "runner.h"
#include "labels.h"

int run_tokens()
{
    for (int i = 0; i < DIPLO_ARRAY_SIZE; i++)
    {
        Program.array[i] = 0;
    }
    int labelLine;
    bool changedI = false;

    int i = 0; // Instruction pointer

    while (true)
    {
        switch (Lines[i].statement)
        {
            case STATEMENT_OUT:
                putchar(Program.array[Program.pointer]);
                break;

            case STATEMENT_GET:
                Program.array[Program.pointer] = (char)getchar();
                break;

            case STATEMENT_INSERT:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                switch (Lines[i].args[0].argSign)
                {
                    int toCalculate;

                    case 0:
                        Program.array[Program.pointer] = Lines[i].args[0].argInt;
                        break;

                    case SIGN_PLUS:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.array[Program.pointer] += toCalculate;
                        break;

                    case SIGN_MINUS:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.array[Program.pointer] -= toCalculate;
                        break;
                    
                    case SIGN_MULTIPLY:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.array[Program.pointer] *= toCalculate;
                        break;

                    case SIGN_DIVIDE:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.array[Program.pointer] /= toCalculate;
                        break;

                    case SIGN_MODULO:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.array[Program.pointer] %= toCalculate;
                        break;
                    
                    default:
                        break;
                }
                break;

            case STATEMENT_INSERTL:
                int tempPointer = Program.pointer;
                for (int j = 0; j < Lines[i].argsCount; j++)
                {
                    Program.array[tempPointer] = Lines[i].args[j].argInt;
                    tempPointer++;
                }
                
                break;

            case STATEMENT_POINTER:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                switch (Lines[i].args[0].argSign)
                {
                    int toCalculate;

                    case 0:
                        Program.pointer = Lines[i].args[0].argInt;
                        break;

                    case SIGN_PLUS:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.pointer += toCalculate;
                        break;

                    case SIGN_MINUS:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.pointer -= toCalculate;
                        break;
                    
                    case SIGN_MULTIPLY:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.pointer *= toCalculate;
                        break;

                    case SIGN_DIVIDE:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.pointer /= toCalculate;
                        break;

                    case SIGN_MODULO:
                        toCalculate = Lines[i].args[0].argInt ? Lines[i].args[0].argInt : 1;
                        Program.pointer %= toCalculate;
                        break;
                    
                    default:
                        break;
                }

                break;

            case STATEMENT_EXIT:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                return Lines[i].args[0].argInt;
                break;

            case STATEMENT_COMP:
                if (Lines[i].argsCount != 2)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected 2 arguments on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }

                int compElems[2];
                for (int j = 0; j < 2; j++)
                {
                    // if (Lines[i].args[j].argStr[0] == '\0')
                    // {
                    //     char error[MAX_ERR_SIZE];
                    //     sprintf(error, "Expected argument on line %d.", i+1);
                    //     return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                    // }
                    if (Lines[i].args[j].argStr[0] == '$')
                    {
                        if (strcmp(Lines[i].args[j].argStr, VAR_POINTER) == 0)
                        {
                            compElems[j] = Program.pointer;
                        }
                        else if (strcmp(Lines[i].args[j].argStr, VAR_VALUE) == 0)
                        {
                            compElems[j] = Program.array[Program.pointer];
                        }
                        else
                        {
                            char error[MAX_ERR_SIZE];
                            sprintf(error, "Unknown variable %s on line %d.", Lines[i].args[j].argStr, i+1);
                            return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                        }
                    }
                    else
                    {
                        compElems[j] = Lines[i].args[j].argInt;
                    }
                }

                Program.lastComp.eq = false;
                Program.lastComp.notEq = false;
                Program.lastComp.less = false;
                Program.lastComp.lessEq = false;
                Program.lastComp.greater = false;
                Program.lastComp.greaterEq = false;

                if (compElems[0] == compElems[1])
                {
                    Program.lastComp.eq = true;
                }
                else if (compElems[0] != compElems[1])
                {
                    Program.lastComp.notEq = true;
                }
                else if (compElems[0] > compElems[1])
                {
                    Program.lastComp.greater = true;
                }
                else if (compElems[0] < compElems[1])
                {
                    Program.lastComp.less = true;
                }
                else if (compElems[0] >= compElems[1])
                {
                    Program.lastComp.greaterEq = true;
                }
                else if (compElems[0] <= compElems[1])
                {
                    Program.lastComp.lessEq = true;
                }
                
                break;

            case STATEMENT_JUMP:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                int labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                i = labelLine-1;
                changedI = true;

                break;

            case STATEMENT_JE:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.eq)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;
            
            case STATEMENT_JNE:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.notEq)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;

            case STATEMENT_JG:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.greater)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;

            case STATEMENT_JL:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.less)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;

            case STATEMENT_JGE:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.greaterEq)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;

            case STATEMENT_JLE:
                if (Lines[i].argsCount == 0)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument on line %d.", i+1);
                    return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
                }
                labelLine = get_label_line(Lines[i].args[0].argStr);
                if (labelLine == -1)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Unknown label %s on line %d.", Lines[i].args[0].argStr, i+1);
                    return derr(ERR_UNKNOWN_LABEL, error, i+1);
                }
                if (Program.lastComp.lessEq)
                {
                    i = labelLine-1;
                    changedI = true;
                }

                break;
            
            default:
                break;
        }

        if (i == Program.lines) return 0;
        i++;
    }

    if (config_flag_exists('d'))
    {
        gray();
        printf("\n\n\nDebug: [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", Program.array[0], Program.array[1], Program.array[2], Program.array[3], Program.array[4], Program.array[5], Program.array[6], Program.array[7], Program.array[8], Program.array[9]);
        color_reset();
    }
    
    return 0;
}