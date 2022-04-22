#include <stdio.h>
#include <math.h>
#include "errors.h"
#include "constants.h"
#include "colors.h"

int derr(const int errorCode, char *message, const int line)
{
    // -> *131072 to add 17x '0' (131072=2^17)
    const long finalCode = line*pow(2, 17) + errorCode;
    red_bold();
    printf("\n/!\\ (DIPLO_ERR:%#x) %s ", finalCode, MSG_FATAL_ERROR);
    color_reset();
    printf("%s", message);
    return 1;
}