#include "malloc.h"

int init_env()
{
    g_env.initialized = 1;
    g_env.pagesize = getpagesize();
    g_env.tiny_zone = set_zone(TINY);
    g_env.small_zone = set_zone(SMALL);
    return 1;
}
