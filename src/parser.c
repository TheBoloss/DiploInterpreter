#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "str.h"
#include "messages.h"
#include "errors.h"

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
    char lines[MAX_LINE_NUMBER][MAX_LINE_SIZE];
    int linesNumber;
    unsigned char array[DIPLO_ARRAY_SIZE];
    int pointer;
    int loopDepth;
} program;

int parse_line(const int lineNumber);
int search_line(char *search, int occurence, int reverse);

int parse(FILE *inputFile)
{
    besideExecutionSettings.executionDebug = 0;
    besideExecutionSettings.showExecutionTime = 0;

    currentLine.number = 1;
    program.pointer = 0;
    program.loopDepth = 0;
    for (int i = 0; i < DIPLO_ARRAY_SIZE; i++)
    {
        program.array[i] = 0;
    }
    

    int fileLineNumber = 0;
    char tempLineRaw[MAX_LINE_SIZE];
    while (fgets(tempLineRaw, MAX_LINE_SIZE, inputFile) != NULL)
    {
        strcpy(program.lines[fileLineNumber], tempLineRaw);
        program.linesNumber++;
        fileLineNumber++;
    }

    for (int i = 1; i <= program.linesNumber; i++)
    {
        if(parse_line(i)) return 1;
    }
    
    if(parse_line(1)) return 1;
    
    if (program.loopDepth > 0)
    {
        printf("%#x%s Invalid loop depth at the end of program.", ERR_LOOP_DEPTH, MSG_FATAL_ERROR, currentLine.trimmed, currentLine.number);
        return 1;
    }
    printf("\n\n\nDebug: [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]", program.array[0], program.array[1], program.array[2], program.array[3], program.array[4], program.array[5], program.array[6], program.array[7], program.array[8], program.array[9]);

    return 0;
}

int parse_line(const int lineNumber)
{
    strcpy(currentLine.raw, program.lines[lineNumber-1]);
    currentLine.number = lineNumber;
    // printf("Received parse: %d (%s)\n", lineNumber, currentLine.raw);

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
                char error[MAX_ERR_SIZE];
                sprintf(error, "Expected argument after '%s' on line %d.", currentLine.exploded.space.content[0], currentLine.number);
                return derr(ERR_EXPECTED_ARGUMENT, error);
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
                char error[MAX_ERR_SIZE];
                sprintf(error, "Invalid argument '%s' on line %d.", currentLine.exploded.space.content[1], currentLine.number);
                return derr(ERR_INVALID_ARGUMENT, error);
            }
        }
        else if (strcmp(statementToLower, "ptr") == 0 || strcmp(statementToLower, "pointer") == 0)
        {
            if (currentLine.exploded.space.length < 2)
            {
                char error[MAX_ERR_SIZE];
                sprintf(error, "Expected argument after '%s' on line %d.", currentLine.exploded.space.content[0], currentLine.number);
                return derr(ERR_EXPECTED_ARGUMENT, error);
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
                char error[MAX_ERR_SIZE];
                sprintf(error, "Invalid argument '%s' on line %d.", currentLine.exploded.space.content[1], currentLine.number);
                return derr(ERR_INVALID_ARGUMENT, error);
            }
        }
        else if (strcmp(statementToLower, "out") == 0)
        {
            putchar(program.array[program.pointer]);
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
                char error[MAX_ERR_SIZE];
                sprintf(error, "Expected argument after '%s' on line %d.", currentLine.exploded.space.content[0], currentLine.number);
                return derr(ERR_EXPECTED_ARGUMENT, error);
            }

            if (strcmp(currentLine.exploded.space.content[1], "repeat"))
            {
                printf("%d-%d\n", currentLine.number, search_line("End Repeat", program.loopDepth-1, 1));

                if (currentLine.exploded.space.length < 3)
                {
                    char error[MAX_ERR_SIZE];
                    sprintf(error, "Expected argument after '%s' on line %d.", currentLine.trimmed, currentLine.number);
                    return derr(ERR_EXPECTED_ARGUMENT, error);
                }

                int loopStartLine = currentLine.number;
                int loopEndLine = search_line("End Repeat", program.loopDepth-1, 1);
                
                int repeatNumber = atoi(currentLine.exploded.space.content[2]);
                for (int i = 0; i < repeatNumber; i++)
                {
                    for (int j = 1; j < loopEndLine; j++)
                    {
                        if (j > loopStartLine) parse_line(j);
                    }
                    
                }
                
            }
        }
        else if (strcmp(statementToLower, "end") == 0)
        {
            program.loopDepth--;
            if (program.loopDepth < 0)
            {
                char error[MAX_ERR_SIZE];
                sprintf(error, "Invalid loop ending at '%s' on line %d.", currentLine.trimmed, currentLine.number);
                return derr(ERR_LOOP_DEPTH, error);
            }
        }
        else
        {
            char error[MAX_ERR_SIZE];
            sprintf(error, "Unknown statement '%s' on line %d.", currentLine.exploded.space.content[0], currentLine.number);
            return derr(ERR_UNKNOWN_STATEMENT, error);
        }
    }

    return 0;
}

int search_line(char *search, int occurence, int reverse)
{
    int found = 0;
    int matchLines[MAX_LINE_NUMBER];
    int matchI = 0;

    char searchFormatted[MAX_LINE_SIZE];
    strcpy(searchFormatted, search);
    str_tolower(searchFormatted);

    for (int i = 0; i <= program.linesNumber; i++)
    {
        // To lower and trim
        char line[MAX_LINE_SIZE];
        if (reverse)
        {
            strcpy(line, program.lines[program.linesNumber-i]);
        }
        else
        {
            strcpy(line, program.lines[i]);
        }
        str_tolower(line);
        char *lineTrimmed = str_trim(line);
        strcpy(line, lineTrimmed);
        if (strcmp(searchFormatted, line) == 0)
        {
            found = 1;
            matchLines[matchI] = i;
            matchI++;
        }
    }
    
    if (reverse) return found
        ? (matchLines[occurence]
            ? program.linesNumber-(matchLines[occurence]) + 1
            : 0)
        : 0;
    return found
        ? (matchLines[occurence]
            ? matchLines[occurence] + 1
            : 0)
        : 0;
}