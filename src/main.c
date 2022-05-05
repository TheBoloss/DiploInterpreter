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
#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif
#include "constants.h"
#include "user/config.h"
#include "user/program.h"
#include "tokens.h"
#include "tokenizer.h"
#include "prerunner.h"
#include "runner.h"
#include "config_flags.h"
#include "colors.h"
#include "debugger/dumper.h"

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
        printf("Eug%cne Villotte (https://github.com/TheBoloss/Diplo)\n\n", 138);
        blue_bold();
        printf("Usage: ");
        white();
        printf("%s ", argv[0]);
        yellow();
        printf("<InputFile> ");
        magenta();
        printf("[Config]\n");
        gray();
        printf("\nPress ENTER to exit\n");
        getchar();
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
    int prerunnerIndexLabelsRet = index_labels(file);
    if (prerunnerIndexLabelsRet != 0) return prerunnerIndexLabelsRet;
    int runnerRet = run_tokens();
    // if (runnerRet != 0) return runnerRet;


    // int parseReturn = parse(file);
    fclose(file);

    gettimeofday(&stop, NULL);
    double executionTime = (stop.tv_sec + stop.tv_usec / 1e6 -
                        start.tv_sec - start.tv_usec / 1e6) * 1000;
    if (!runnerRet && config_flag_exists('t'))
    {
        green();
        printf("\n\nScript executed successfully in %f ms.", executionTime);
        color_reset();
    }

    if(runnerRet) printf("\nProgram returned error.\n");

    if (config_flag_exists('e'))
    {
        return runnerRet;
    }
    
    gray();
    printf("%c\nPress ENTER to exit\n", 13);
    getchar();
    color_reset();
    return runnerRet;
}