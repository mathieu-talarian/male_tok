#include "malloc.h"

int init_env()
{
    g_env.pagesize = getpagesize();
    g_env.func_m[0] = tiny_m;
    g_env.func_m[1] = small_m;
    g_env.func_m[2] = large_m;
    g_env.tiny = set_tiny();
    g_env.small = set_small();
    return 1;
}
