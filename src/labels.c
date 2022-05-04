#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "user/program.h"
#include "labels.h"

bool label_exists(char *label)
{
    for (int i = 0; i < Program.labelsCount; i++)
    {
        if (strcmp(label, Program.labels[i].name) == 0)
        {
            return true;
        }
    }
    return false;
}

int get_label_line(char *label)
{
    for (int i = 0; i < Program.labelsCount; i++)
    {
        if (strcmp(label, Program.labels[i].name) == 0)
        {
            return Program.labels[i].lineNumber;
        }
    }
    return -1;
}