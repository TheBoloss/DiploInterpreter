#ifdef _WIN32
#include <Windows.h> // Windows
#else
#include <unistd.h> // Linux
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"
#include "messages.h"
#include "parser.h"


struct settings
{
    char inputFName[INPUT_FNAME_MAX_LENGTH];
    char configFlags[CONFIG_FLAGS_MAX_LENGTH];
} globalSettings;


int main(int argc, char *argv[])
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    if (argc < 2)
    {
        return no_file_specified_message();
    }
    

    for (int i = 1; i < argc; i+=2)
    {
        if (!strcmp(argv[i], "-h"))
        {
            printf("Usage: %s -i <File>\n", argv[0]);
            printf("Optional arguments:\n");
            printf("\t-c\tConfig\n");
            printf("\t-h\tDisplay this help message\n");
            return 0;
        }
        if (!strcmp(argv[i], "-i") && i < argc - 1)
        {
            strncpy(globalSettings.inputFName, argv[i + 1], INPUT_FNAME_MAX_LENGTH - 1);
        } else
        {
            return no_file_specified_message();
        }
    }

    FILE *file = fopen(globalSettings.inputFName, "r");
    if (file == NULL)
    {
        printf("Fatal: Error opening file. The file '%s' cannot be opened. Please check if it exists and retry.\n", globalSettings.inputFName);
        return 1;
    }

    // printf(argv[i]);
    // welcome_message();
    // execute_program(file);
    int parseReturn = parse(file);

    gettimeofday(&stop, NULL);
    double executionTime = (stop.tv_sec + stop.tv_usec / 1e6 - // 1e6 for seconds
                        start.tv_sec - start.tv_usec / 1e6) * 1000;

    printf("\n\nExecuted program in %f ms.\n", executionTime);

    if(parseReturn) printf("Program returned error.");
    return parseReturn;
}