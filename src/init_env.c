#include "malloc.h"

int init_env()
{
    g_env.initialized = 1;
    g_env.pagesize = getpagesize();
    return 1;
}
