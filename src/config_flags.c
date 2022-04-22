#include "config_flags.h"
#include "constants.h"
#include "user/config.h"

int config_flag_exists(const char flag)
{
    for (int i = 0; i < CONFIG_FLAGS_MAX_LENGTH; i++)
    {
        if (GlobalSettings.configFlags[i] == flag)
        {
            return 1;
        }
    }
    return 0;
}