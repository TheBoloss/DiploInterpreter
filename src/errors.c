#include <stdio.h>
#include "errors.h"
#include "constants.h"

int derr(const int errorCode, char *message)
{
    printf("/!\\ (%#x) %s %s", errorCode, MSG_FATAL_ERROR, message);
    return 1;
}