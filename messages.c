#include <stdio.h>
#include "messages.h"

void welcome_message()
{
    printf("             _  _  _ \n");
    printf("          __| |(_)(_)\n");
    printf("         / _` || || |\n");
    printf("         \\__/_||_||_|\n\n");

    printf("###############################\n");
    printf("#                             #\n");
    printf("#    DiplodocusInterpreter    #\n");
    printf("#         - Welcome -         #\n");
    printf("#                             #\n");
    printf("###############################\n");
    printf("https://vlte.eu Eugene Villotte\n\n");

    // printf("Press Enter to continue...");
    // scanf("a");
    // system("cls");
    
    printf("\n\n");
    
}

int no_file_specified_message()
{
    printf("Fatal: No input file specified. Specify -h flag for more help.\n");
    return 1;
}