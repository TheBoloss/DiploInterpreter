#include <stdio.h>

void black()
{
    printf("\033[30m");
}

void red()
{
    printf("\033[0;31m");
}

void green()
{
    printf("\033[0;32m");
}

void yellow()
{
    printf("\033[0;33m");
}

void blue()
{
    printf("\033[0;34m");
}

void magenta()
{
    printf("\033[0;35m");
}

void cyan()
{
    printf("\033[0;36m");
}

void white()
{
    printf("\033[0;37m");
}

void gray()
{
    printf("\033[0;90m");
}

void color_reset()
{
    printf("\033[0m");
}

void black_bold()
{
    printf("\033[1;30m");
}

void red_bold()
{
    printf("\033[1;31m");
}

void green_bold()
{
    printf("\033[1;32m");
}

void yellow_bold()
{
    printf("\033[1;33m");
}

void blue_bold()
{
    printf("\033[1;34m");
}

void magenta_bold()
{
    printf("\033[1;35m");
}

void cyan_bold()
{
    printf("\033[1;36m");
}

void white_bold()
{
    printf("\033[1;37m");
}

void gray_bold()
{
    printf("\033[1;90m");
}