/* Names:
    - TiboTinyInterpreter TTI
    - AnotherFuckingProgrammingLanguage AFPL
 */

#ifdef _WIN32
#include <Windows.h> // Windows
#else
#include <unistd.h> // Linux
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "messages.c"

#define INPUT_FNAME_MAX_LENGTH 100
#define CONFIG_FLAGS_MAX_LENGTH 20

struct settings
{
    char inputFName[INPUT_FNAME_MAX_LENGTH];
    char configFlags[CONFIG_FLAGS_MAX_LENGTH];
} globalSettings;

void execute_program(FILE *file)
{
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }
}

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
            // continue;
        }
        if (!strcmp(argv[i], "-i") && i < argc - 1)
        {
            strncpy(globalSettings.inputFName, argv[i + 1], INPUT_FNAME_MAX_LENGTH - 1);
            printf("Program name is: %s\n\n", globalSettings.inputFName);
            // continue;
        } else
        {
            return no_file_specified_message();
        }
        if (!strcmp(argv[i], "-c") && i < argc - 1)
        {
            strncpy(globalSettings.configFlags, argv[i + 1], CONFIG_FLAGS_MAX_LENGTH - 1);
            // continue;
        }
    }

    FILE *file = fopen(globalSettings.inputFName, "r");
    if (file == NULL)
    {
        printf("Fatal: Error opening file. The file '%s' cannot be opened. Please check if it exists and retry.\n", globalSettings.inputFName);
        return 1;
    }

    // printf(argv[i]);
    welcome_message();
    execute_program(file);


    // if(!isFileSpecified) {
    //     return noFileSpecifiedMessage();
    // }

    gettimeofday(&stop, NULL);
    double executionTime = (stop.tv_sec + stop.tv_usec / 1e6 - // 1e6 for seconds
                        start.tv_sec - start.tv_usec / 1e6) * 1000;

    printf("\n\nExecuted program in %f ms.\n", executionTime);

    return 0;
}