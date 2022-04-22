#ifndef DEF_USER_CONFIG
#define DEF_USER_CONFIG

#include "../constants.h"

typedef struct
{
    char inputFName[INPUT_FNAME_MAX_LENGTH];
    char configFlags[CONFIG_FLAGS_MAX_LENGTH];
} settings;

extern settings GlobalSettings;

#endif