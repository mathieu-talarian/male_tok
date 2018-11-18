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
        find_debug(d);
    if (IS_DEBUG(g_env.env))
    {
        ft_putendl("Debug on");
        g_cpt[0] = 0;
        g_cpt[1] = 0;
        g_cpt[2] = 0;
    }
    return (1);
}