#include "malloc.h"

int init_env()
{
    g_env.initialized = 1;
    g_env.pagesize = getpagesize();
    g_env.tiny = set_tiny();
    g_env.small = set_small();
    return 1;
}
