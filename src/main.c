/*
  Diplo
  2022. Eugène Villotte
*/


#ifdef _WIN32
#include <Windows.h> // Windows
#else
#include <unistd.h> // Linux
#endif
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
// #include <conio.h>
#include "constants.h"
#include "user/config.h"
#include "user/program.h"
#include "tokens.h"
// #include "parser.h"
#include "tokenizer.h"
#include "preprocessor.h"
#include "config_flags.h"
#include "colors.h"

settings GlobalSettings;
program Program;
LineTokens Lines[MAX_LINE_NUMBER];


int main(int argc, char *argv[])
{
    // FILE *keyFile = NULL;
    // keyFile = fopen(BETA_KEY, "r");
    // if (keyFile == NULL)
    // {
    //     red_bold();
    //     printf("Beta testers only: you need to have the key file in ./key/.\n");
    //     color_reset();
    //     return 1;
    // }
    // fclose(keyFile);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    // Input file argument
    if (argv[1])
    {
        strncpy(GlobalSettings.inputFName, argv[1], INPUT_FNAME_MAX_LENGTH - 1);
    }
    else
    {
        printf("Diplo v%s\n", DIPLO_VERSION);
        printf("Eug%cne Villotte\n\n", 138);
        blue_bold();
        printf("Usage: ");
        white();
        printf("%s ", argv[0]);
        yellow();
        printf("<InputFile> ");
        magenta();
        printf("[Config]\n");
        color_reset();
        return 0;
    }

    // Config argument
    if (argv[2])
    {
        strncpy(GlobalSettings.configFlags, argv[2], CONFIG_FLAGS_MAX_LENGTH - 1);
        gray();
        size_t configLength = strlen(argv[2]);
        if (config_flag_exists('d'))
        {
            for (size_t i = 0; i < configLength; i++)
            {
                printf("Config '%c' enabled.\n", argv[2][i]);
            }
        }
        color_reset();
    }

    FILE *file = fopen(GlobalSettings.inputFName, "r");
    if (file == NULL)
    {
        red_bold();
        printf("Fatal: ");
        color_reset();
        printf("Error opening file. The file '%s' cannot be opened. Please check if it exists and retry.\n", GlobalSettings.inputFName);
        return 1;
    }

    int tokenizerRet = tokenize_file(file);
    if (tokenizerRet != 0) return tokenizerRet;
    int preprocessorIndexLabelsRet = index_labels(file);
    if (preprocessorIndexLabelsRet != 0) return preprocessorIndexLabelsRet;


    // int parseReturn = parse(file);
    // fclose(file);

    // gettimeofday(&stop, NULL);
    // double executionTime = (stop.tv_sec + stop.tv_usec / 1e6 -
    //                     start.tv_sec - start.tv_usec / 1e6) * 1000;
    // if (!parseReturn && !config_flag_exists('t'))
    // {
    //     green();
    //     printf("\n\nScript executed successfully in %f ms.", executionTime);
    //     color_reset();
    // }

    // if(parseReturn) printf("\nProgram returned error.\n");

    // if (config_flag_exists('e'))
    // {
    //     return 0;
    // }
    // gray();
    // printf("Press any key to exit\n");
    // getch();
    // color_reset();
    // return parseReturn;
}