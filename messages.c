void welcome_message()
{
    printf("       _____  _____  ___       \n");
    printf("      |_   _||_   _||_ _|      \n");
    printf("        | |    | |   | |       \n");
    printf("        |_|    |_|  |___|      \n\n");

    printf("###############################\n");
    printf("#                             #\n");
    printf("#    Tibo Tiny Interpreter    #\n");
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