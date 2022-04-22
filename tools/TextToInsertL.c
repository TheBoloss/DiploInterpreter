#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str = argv[1];
    printf("\033[0;32mInsertL ");
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%d", str[i]);
        if (i != strlen(str)-1) printf(", ");
    }
    printf("\033[0m");
    
    return 0;
}
