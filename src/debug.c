#include "malloc.h"

static void find_debug(char *d)
{
    if (ft_strcmp("true", d) == 0)
    {
        DEBUG_ON(g_env.env);
    }
}

int debug()
{
    char *d;

    d = getenv("DEBUG");
    if (d != NULL)
    {
        find_debug(d);
    }
    if (IS_DEBUG(g_env.env))
    {
        ft_putendl("Debug on");
    }
    return (1);
}