#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "str.h"
#include "messages.h"
#include "errors.h"
#include "std_functions.h"

struct besideExecutionSettings
{
    char *title;
    int executionDebug;
    int showExecutionTime;
} besideExecutionSettings;

struct
{
    char raw[MAX_LINE_SIZE];
    char *trimmed;
    int number;
    struct
    {
        struct
        {
            char **content;
            int length;
        } space;
    } exploded;
} currentLine;

struct
{
    unsigned char array[DIPLO_ARRAY_SIZE];
    int pointer;
    int loopDepth;
} program;

int parse(FILE *inputFile)
{
    besideExecutionSettings.executionDebug = 0;
    besideExecutionSettings.showExecutionTime = 0;

    // char lineContentRaw[MAX_LINE_SIZE];
    // unsigned char arr[DIPLO_ARRAY_SIZE] = {0};
    // program.array;
    currentLine.number = 1;
    program.pointer = 0;
    program.loopDepth = 0;
    for (int i = 0; i < DIPLO_ARRAY_SIZE; i++)
    {
        program.array[i] = 0;
    }
    

    while (fgets(currentLine.raw , MAX_LINE_SIZE, inputFile) != NULL)
    {
        // printf("%s\n", currentLine.raw);
        currentLine.trimmed = str_trim(currentLine.raw);

        // If line is not empty
        if(strlen(currentLine.trimmed) != 0)
        {
            currentLine.exploded.space.content = split(currentLine.trimmed, " ", 0, &currentLine.exploded.space.length);
            
            // printf("Line %d length: %d\n", currentLine.number, currentLine.exploded.space.length);

            char statementToLower[MAX_LINE_SIZE];
            strcpy(statementToLower, currentLine.exploded.space.content[0]);
            str_tolower(statementToLower);
            
            // Comments
            if (strcmp(statementToLower, "//") == 0) {}
            else if (strcmp(statementToLower, "insert") == 0)
            {
                if (currentLine.exploded.space.length < 2)
                {
                    printf("%#x%s Expected argument after '%s' on line %d.", ERR_EXPECTED_ARGUMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[0], currentLine.number);
                    return 1;
                }

                // Insert +
                if (currentLine.exploded.space.content[1][0] == '+')
                {
                    if(strlen(currentLine.exploded.space.content[1]) < 2)
                    {
                        program.array[program.pointer]++;
                    }
                    // +n
                    else
                    {
                        char *toAddStr = currentLine.exploded.space.content[1] + 1;
                        int toAdd = atoi(toAddStr);
                        program.array[program.pointer] += toAdd;
                    }
                }
                // Insert -
                else if (currentLine.exploded.space.content[1][0] == '-')
                {
                    if(strlen(currentLine.exploded.space.content[1]) < 2)
                    {
                        program.array[program.pointer]--;
                    }
                    // -n
                    else
                    {
                        char *toAddStr = currentLine.exploded.space.content[1] + 1;
                        int toAdd = atoi(toAddStr);
                        program.array[program.pointer] -= toAdd;
                    }
                }
                // If argument starts with a num
                else if (currentLine.exploded.space.content[1][0] >= 48 && currentLine.exploded.space.content[1][0] <= 57)
                {
                    int newValue = atoi(currentLine.exploded.space.content[1]);
                    program.array[program.pointer] = newValue;
                }
                else
                {
                    printf("%#x%s Invalid argument '%s' on line %d.", ERR_INVALID_ARGUMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[1], currentLine.number);
                    return 1;
                }
            }
            else if (strcmp(statementToLower, "ptr") == 0 || strcmp(statementToLower, "pointer") == 0)
            {
                if (currentLine.exploded.space.length < 2)
                {
                    printf("%#x%s Expected argument after '%s' on line %d.", ERR_EXPECTED_ARGUMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[0], currentLine.number);
                    return 1;
                }

                // Ptr +
                if (currentLine.exploded.space.content[1][0] == '+')
                {
                    if(strlen(currentLine.exploded.space.content[1]) < 2)
                    {
                        program.pointer++;
                    }
                    // +n
                    else
                    {
                        char *toAddStr = currentLine.exploded.space.content[1] + 1;
                        int toAdd = atoi(toAddStr);
                        program.pointer += toAdd;
                    }
                }
                // Ptr -
                else if (currentLine.exploded.space.content[1][0] == '-')
                {
                    if(strlen(currentLine.exploded.space.content[1]) < 2)
                    {
                        program.pointer--;
                    }
                    // -n
                    else
                    {
                        char *toAddStr = currentLine.exploded.space.content[1] + 1;
                        int toAdd = atoi(toAddStr);
                        program.pointer -= toAdd;
                    }
                }
                // If argument starts with a num
                else if (currentLine.exploded.space.content[1][0] >= 48 && currentLine.exploded.space.content[1][0] <= 57)
                {
                    int newValue = atoi(currentLine.exploded.space.content[1]);
                    program.pointer = newValue;
                }
                else
                {
                    printf("%#x%s Invalid argument '%s' on line %d.", ERR_INVALID_ARGUMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[1], currentLine.number);
                    return 1;
                }
            }
            else if (strcmp(statementToLower, "out") == 0)
            {
                printf("%c", program.array[program.pointer]);
            }
            else if (strcmp(statementToLower, "get") == 0)
            {
                // scanf("%c", program.array[program.pointer]);
                program.array[program.pointer] = getchar();
            }
            // Loops
            else if (strcmp(statementToLower, "begin") == 0)
            {
                program.loopDepth++;

                if (currentLine.exploded.space.length < 2)
                {
                    printf("%#x%s Expected argument after '%s' on line %d.", ERR_EXPECTED_ARGUMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[0], currentLine.number);
                    return 1;
                }

                if (strcmp(currentLine.exploded.space.content[1], "repeat"))
                {
                    // How to repeat the code?
                }
            }
            else if (strcmp(statementToLower, "end") == 0)
            {
                program.loopDepth--;
                if (program.loopDepth < 0)
                {
                    printf("%#x%s Invalid loop ending at '%s' on line %d.", ERR_LOOP_DEPTH, MSG_FATAL_ERROR, currentLine.trimmed, currentLine.number);
                    return 1;
                }
            }
            else
            {
                printf("%#x%s Unknown statement '%s' on line %d.", ERR_UNKNOWN_STATEMENT, MSG_FATAL_ERROR, currentLine.exploded.space.content[0], currentLine.number);
                return 1;
            }
        }
        currentLine.number++;
    }

    if (program.loopDepth > 0)
    {
        printf("%#x%s Invalid loop depth at the end of program.", ERR_LOOP_DEPTH, MSG_FATAL_ERROR, currentLine.trimmed, currentLine.number);
        return 1;
    }
    printf("\n%d, %d, %d, %d, %d, %d, %d, %d, %d, %d", program.array[0], program.array[1], program.array[2], program.array[3], program.array[4], program.array[5], program.array[6], program.array[7], program.array[8], program.array[9]);

    // char _lineContent[MAX_LINE_SIZE];
    // int _lineNumber = 1;
    // while (fgets(_lineContent, MAX_LINE_SIZE, inputFile) != NULL)
    // {
    //     char *_lineContentTrimmed = str_trim(_lineContent);

    //     // Debug only
    //     if(EXECUTION_DEBUG) printf("Reading line %d\n%s\n", _lineNumber, _lineContent);

    //     // If line is not empty
    //     if (strlen(_lineContentTrimmed) != 0)
    //     {
    //         int explodedTrimmedLength = 0;
    //         int explodedLength = 0;
    //         split(_lineContent, " ", 0, &explodedLength);
    //         char **exploded = split(_lineContentTrimmed, " ", 0, &explodedTrimmedLength);
            
    //         char *mainStatement = exploded[0];
    //         int mainStatementExplodedLength = 0;
    //         char **mainStatementExploded = split(mainStatement, ".", 0, &mainStatementExplodedLength);

    //         // console.* functions
    //         if (strcmp(mainStatementExploded[0], "console") == 0)
    //         {
    //             if (mainStatementExplodedLength < 2)
    //             {
    //                 printf("Statement error: Expected expression after '%s' on line %d.", mainStatementExploded[0], _lineNumber);
    //                 return 1;
    //             }

    //             // console.out
    //             if (strcmp(mainStatementExploded[1], "out") == 0) 
    //             {
    //                 if(explodedTrimmedLength < 2)
    //                 {
    //                     printf("Argument error: Expecting argument after '%s' on line %d.", mainStatement, _lineNumber);
    //                     return 1;
    //                 }

    //                 char *quoteContent = str_get_quotes_content(_lineContent);
    //                 std_console_out(&quoteContent);
    //             }
    //             else
    //             {
    //                 printf("Statement error: '%s' is not a function of '%s' on line %d.", mainStatementExploded[1], mainStatementExploded[0], _lineNumber);
    //                 return 1;
    //             }
    //         } else
    //         {
    //             printf("Statement error: Unknown '%s' on line %d.", mainStatement, _lineNumber);
    //             return 1;
    //         }
    //     }

        

    //     _lineNumber++;
    // }

    return 0;
}