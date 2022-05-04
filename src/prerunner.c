#include <stdio.h>
#include <string.h>
#include "prerunner.h"
#include "constants.h"
#include "user/config.h"
#include "user/program.h"
#include "tokens.h"
#include "colors.h"
#include "config_flags.h"
#include "errors.h"

int index_labels(FILE *file)
{
    for (int i = 0; i < Program.lines; i++)
    {
        if (Lines[i].statement == STATEMENT_LABEL)
        {
            if (Lines[i].args[0].argStr[0] == '\0')
            {
                char error[MAX_ERR_SIZE];
                sprintf(error, "Expected argument on line %d.", i+1);
                return derr(ERR_EXPECTED_ARGUMENT, error, i+1);
            }

            Program.labels[Program.labelsCount].lineNumber = i;
            strcpy(Program.labels[Program.labelsCount].name, Lines[i].args[0].argStr);
            Program.labelsCount++;
        }
    }
    
    if (config_flag_exists('d'))
    {
        gray();
        for (int i = 0; i < Program.labelsCount; i++)
        {
            printf("Label \"%s\" on line %d.\n", Program.labels[i].name, Program.labels[i].lineNumber+1);
        }
        color_reset();
    }

    return 0;
}