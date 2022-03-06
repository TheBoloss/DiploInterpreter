#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "str.h"
#include "messages.h"
#include "errors.h"

int parse(FILE *inputFile)
{
    char _lineContent[MAX_LINE_SIZE];
    int _lineNumber = 1;
    while (fgets(_lineContent, MAX_LINE_SIZE, inputFile) != NULL)
    {
        char *_lineContentTrimmed = str_trim(_lineContent);

        // Debug only
        if(EXECUTION_DEBUG) printf("Executing line %d\n%s\n", _lineNumber, _lineContent);

        // If line is not empty
        if (strlen(_lineContentTrimmed) != 0)
        {
            int explodedLength = 0;
            char **exploded = split(_lineContentTrimmed, " ", 0, &explodedLength);
            
            char *mainStatement = exploded[0];
            int mainStatementExplodedLength = 0;
            char **mainStatementExploded = split(mainStatement, ".", 0, &mainStatementExplodedLength);

            // console.* functions
            if (strcmp(mainStatementExploded[0], "console") == 0)
            {
                if (mainStatementExplodedLength < 2)
                {
                    printf("Statement error: Expected expression after '%s' on line %d.", mainStatementExploded[0], _lineNumber);
                    return 1;
                }

                // console.out
                if (strcmp(mainStatementExploded[1], "out") == 0) 
                {
                    if(explodedLength < 2)
                    {
                        printf("Argument error: Expecting argument after '%s' on line %d.", mainStatement, _lineNumber);
                        return 1;
                    }

                    if(str_count_occurrences(exploded[1], '"') % 2)
                    {
                        printf("Quotes error: Invalid quotes on line %d.", _lineNumber);
                        return 1;
                    }
                }
                else
                {
                    printf("Statement error: '%s' is not a function of '%s' on line %d.", mainStatementExploded[1], mainStatementExploded[0], _lineNumber);
                    return 1;
                }
            } else
            {
                printf("Statement error: Unknown '%s' on line %d.", mainStatement, _lineNumber);
                return 1;
            }
        }

        

        _lineNumber++;
    }

    return 0;
}