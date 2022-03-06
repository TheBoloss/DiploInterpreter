#include <stdio.h>
#include "errors.h"

int error_statement(char *message)
{
    printf("Statement error: %s", message);
    return 1;
}