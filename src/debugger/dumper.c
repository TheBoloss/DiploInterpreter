#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../constants.h"
#include "../user/program.h"

// Returns error code
int dump_array(char *array, FILE *outputFile)
{
    if (outputFile == NULL) return 1;

    time_t time_sec;
    time_sec = time(NULL);

    fprintf(outputFile, "{\n");
    fprintf(outputFile, "\t\"time\": \"%d\",\n", time_sec);
    fprintf(outputFile, "\t\"array\": [\n");
    for (int i = 0; i < DIPLO_ARRAY_SIZE; i++)
    {
        fprintf(outputFile, "\t\t\"%d\"", array[i]);
        if (i != DIPLO_ARRAY_SIZE - 1)
        {
            fprintf(outputFile, ",\n");
        }
    }
    fprintf(outputFile, "\n\t]\n");
    fprintf(outputFile, "}");
}

int dump_tokens(LineTokens Lines[])
{

}