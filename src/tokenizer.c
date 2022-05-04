#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user/config.h"
#include "user/program.h"
#include "config_flags.h"
#include "constants.h"
#include "errors.h"
#include "str.h"
#include "colors.h"
#include "tokens.h"
#include "tokenizer.h"
#include "types.h"

int tokenize_file(FILE *file)
{
    if (file == NULL)
    {
        return 1;
    }

    int fileLineNumber = 0;
    char lineContentRaw[MAX_LINE_SIZE];

    // Tokenize each line
    while (fgets(lineContentRaw, MAX_LINE_SIZE, file) != NULL)
    {
        char *lineContentTrimmed = str_trim(lineContentRaw);
        if (config_flag_exists('d'))
        {
            gray();
            printf("%s\n", lineContentTrimmed);
            color_reset();
        }

        Lines[fileLineNumber].lineNumber = fileLineNumber+1;

        int lineTokensCount = 0;
        char **lineTokens = str_explode(lineContentTrimmed, " ", 0, &lineTokensCount);

        // If line is empty, skip it
        if (lineContentTrimmed[0] == '\0')
        {

            Lines[fileLineNumber].statement = 0;
            fileLineNumber++;
            Program.lines = fileLineNumber;
            continue;
        }
        statement_t lineStatement = get_statement(lineTokens[0]);
        // If line has STATEMENT_NULL (0, usually comments //), skip it
        if (lineStatement == 0)
        {
            Lines[fileLineNumber].statement = 0;
            fileLineNumber++;
            Program.lines = fileLineNumber;
            // Lines[i].argsCount = 0;
            continue;
        }
        // Throw error if statement is not valid
        if (lineStatement == -1)
        {
            char error[MAX_ERR_SIZE];
            sprintf(error, "Unknown statement '%s' on line %d.", lineTokens[0], fileLineNumber+1);
            return derr(ERR_UNKNOWN_STATEMENT, error, fileLineNumber+1);
        }
        Lines[fileLineNumber].statement = lineStatement;
        
        char lineArgsInline[MAX_LINE_SIZE] = "";
        for (int i = 1; i < lineTokensCount; i++)
        {
            strcat(lineArgsInline, lineTokens[i]);
            strcat(lineArgsInline, " ");
        }
        
        strcat(lineArgsInline, "\0");
        
        int lineArgsCount = 0;
        char **lineArgs = str_explode(lineArgsInline, ",", 0, &lineArgsCount);

        // Tokenize each argument
        for (int i = 0; i < lineArgsCount; i++)
        {
            Lines[fileLineNumber].argsCount = lineArgsCount;

            char *argTrimmed = str_trim(lineArgs[i]);
            // Debug
            if (config_flag_exists('d'))
            {
                gray();
                printf("\tArg: %s\n", argTrimmed);
                color_reset();
            }

            // Check if arg starts with //
            // if (argTrimmed[0] == '/' && argTrimmed[1] == '/')
            // {
            //     continue;
            // }

            int argNumberStart = 1;
            int isString = true;
            // Detect if arg starts with operator
            if (argTrimmed[0] == SIGN_PLUS)
            {
                Lines[fileLineNumber].args[i].argSign = SIGN_PLUS;
                isString = false;
            }
            if (argTrimmed[0] == SIGN_MINUS)
            {
                Lines[fileLineNumber].args[i].argSign = SIGN_MINUS;
                isString = false;
            }
            if (argTrimmed[0] == SIGN_MULTIPLY)
            {
                Lines[fileLineNumber].args[i].argSign = SIGN_MULTIPLY;
                isString = false;
            }
            if (argTrimmed[0] == SIGN_DIVIDE)
            {
                Lines[fileLineNumber].args[i].argSign = SIGN_DIVIDE;
                isString = false;
            }
            if (argTrimmed[0] == SIGN_MODULO)
            {
                Lines[fileLineNumber].args[i].argSign = SIGN_MODULO;
                isString = false;
            }
            // Detect if arg starts with number
            if (argTrimmed[0] >= '0' && argTrimmed[0] <= '9')
            {
                argNumberStart = 0;
                isString = false;
            }
            // Detect if arg starts with string
            if (!isString)
            {
                Lines[fileLineNumber].args[i].argType = ARG_TYPE_INT;
                int argInt = atoi(argTrimmed + argNumberStart);
                Lines[fileLineNumber].args[i].argInt = argInt;
            }
            else
            {
                Lines[fileLineNumber].args[i].argType = ARG_TYPE_STR;
                strcpy(Lines[fileLineNumber].args[i].argStr, argTrimmed);
            }

            // Debug
            if (config_flag_exists('d'))
            {
                gray();
                printf("\t\tArgInt: %d\n", Lines[fileLineNumber].args[i].argInt);
                printf("\t\tArgSign: %c\n", Lines[fileLineNumber].args[i].argSign);
                printf("\t\tArgStr: %s\n", Lines[fileLineNumber].args[i].argStr);
                color_reset();
            }
        }
        
        fileLineNumber++;
        Program.lines = fileLineNumber;
    }

    // Debug
    // For each in Lines
    for (int i = 0; i < fileLineNumber; i++)
    {
        if (config_flag_exists('d'))
        {
            red();
            printf("Line %d: %d\n", Lines[i].lineNumber, Lines[i].statement);
            color_reset();
        }
    }

    return 0;
}

statement_t get_statement(char *statement)
{
    int found = -1;
    if (strcmp(statement, "//") == 0)
        return 0;
    for (int i = 0; i <= STATEMENT_LABEL; i++)
    {
        char statementLow[MAX_TOKEN_SIZE];
        strcpy(statementLow, statement);
        str_tolower(statementLow);

        if (strcmp(statementLow, STATEMENTS_STR[i]) == 0)
        {
            found = i;
        }
    }
    return found;
}

int is_token_valid(char *token)
{

}