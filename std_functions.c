#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "str.h"
#include "constants.h"

int std_console_out(char **strp)
{
    printf("%s", *strp);
    return 0;
}