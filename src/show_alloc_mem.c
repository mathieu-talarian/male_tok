#include "malloc.h"

static void print_total(UL total)
{
    ft_putstr("Total : ");
    ft_putnbr_ull_endl(total);
}

static UL ull_max(UL t, UL s, UL l)
{
    if (t == s && l == s && l == 0)
        return (0);
    else if (l > s && l > t)
        return (l);
    else if (s > l && s > t)
        return (s);
    else
        return (t);
}

static UL min(UL a, UL b, UL c)
{
    asm("cmp   %1,%0\n"
        "cmova %1,%0\n"
        "cmp   %2,%0\n"
        "cmova %2,%0\n"
        : "+r"(a)
        : "r"(b), "r"(c));
    return (a);
}

static void *_min(void *a, void *b, void *c, UL min)
{
    if (min == (UL)a)
        return a;
    else if (min == (UL)b)
        return b;
    else if (min == (UL)c)
        return c;
    return NULL;
}

static void *addr_min(void *tiny, void *small, void *large)
{
    UL t;
    UL s;
    UL l;
    UL max;

    max = (UL)t + (UL)s + (UL)s + 1;
    printf("%p - %p - %p\n", g_env.tiny, g_env.small, g_env.large);
    t = tiny ? (UL)tiny : max;
    s = small ? (UL)small : max;
    l = large ? (UL)large : max;
    printf("%llu - %llu - %llu\n", t, s, l);
    if (t == s == l)
        return NULL;
    return _min(tiny, small, large, min(t, s, l));
}

static void printf_z(UL *total, int type, t_zone *zone, t_zone **z)
{
    t_chunk *chunk;
    size_t size;

    size = 0;
    chunk = zone->head;
    if (type == TINY)
        ft_putstr("TINY : ");
    else
        pt_putstr("SMALL : ");
    print_add((void *)zone);
    ft_puchar('\n');
    while (chunk)
    {
        if (!IS_FREE(chunk->free))
            printf_c(chunk, total);
        chunk = chunk->next;
    }
}

static void print_zones(UL *total)
{
    void *min;
    t_zone *t;
    t_zone *s;
    t_zone *l;

    while ((min = addr_min(t, s, l)))
        if (min == t)
            printf_z(total, TINY, t, &t);
        else if (min == s)
            printf_z(total, SMALL, s, &s);
        else if (min == l)
            printf_l(total, LARGE, l, &l);
}

void show_alloc_mem()
{
    UL total;

    total = 0;
    print_zones(&total);
    print_total(total);
}
