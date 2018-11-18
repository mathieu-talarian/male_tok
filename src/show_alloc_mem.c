#include "malloc.h"

static void print_total(UL total)
{
    ft_putstr("Total : ");
    ft_putnbr_ull_endl(total);
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
    printf("%llu - %llu - %llu - %llu\n", (UL) a, (UL) b, (UL) c, min);

    if (min == (UL) a)
        return a;
    else if (min == (UL) b)
        return b;
    else if (min == (UL) c)
        return c;
    return NULL;
}

static void *addr_min(void *tiny, void *small, void *large)
{
    UL t;
    UL s;
    UL l;
    UL max;

    t = 0;
    s = 0;
    l = 0;
    max = 0;
    max = (UL) t + (UL) s + (UL) s + 1;
    printf("%p - %p - %p\n", g_env.tiny_zone, g_env.small_zone, g_env.large_zone);
    t = tiny ? (UL) tiny : max;
    s = small ? (UL) small : max;
    l = large ? (UL) large : max;
    printf("%llu - %llu - %llu\n", t, s, l);
    if (t == s == l)
        return NULL;
    return _min(tiny, small, large, min(t, s, l));
}

// static void printf_l(UL *total, int type, t_chunk *chunk, t_chunk **c) {
//   // *c = chunk->next;
// }

static int add_len(UL add)
{
    int len;

    len = 0;
    while (add)
    {
        add /= 16;
        len++;
    }
    return (len);
}

static char *nbr_to_hex_str(UL add)
{
    char *str;
    int   i;
    int   r;
    char *dt;

    i = add_len(add);
    dt = "0123456789abcdef";
    str = map(i + 1);
    str[i] = 0;

    while (add)
    {
        i--;
        r = add % 16;
        str[i] = dt[r];
        add /= 16;
    }
    return (str);
}

static void print_add(void *add)
{
    char *str;

    ft_putstr("0x");
    str = nbr_to_hex_str((UL) add);
    ft_putstr(str);
    munmap(str, ft_strlen(str) + 1);
}

static void printf_c(t_chunk *chunk, UL *total)
{
    print_add((void *) (chunk + 1));
    ft_putstr(" - ");
    print_add((void *) (chunk + 1) + chunk->size);
    ft_putstr(" : ");
    ft_putnbr_ull(chunk->size);
    if (chunk->size > 1)
        ft_putendl(" octets");
    else
        ft_putendl(" octet");
    *total += chunk->size;
}

static void printf_z(UL *total, int type, t_zone **zone)
{
    t_chunk *chunk;
    size_t   size;
    t_zone * z;

    z = *zone;
    size = 0;
    chunk = z->head;
    if (type == TINY)
        ft_putstr("TINY : ");
    else
        ft_putstr("SMALL : ");
    print_add((void *) zone);
    ft_putchar('\n');
    while (chunk)
    {
        if (!chunk->free)
            printf_c(chunk, total);
        chunk = chunk->next;
    }
    *zone = z->next;
}

static void print_zones(UL *total)
{
    void *   min;
    t_zone * t;
    t_zone * s;
    t_chunk *l;

    t = g_env.tiny_zone;
    s = g_env.small_zone;
    l = g_env.large_zone;
    while ((min = addr_min(t, s, l)))
    {
        if (min == t)
            printf_z(total, TINY, &t);
        else if (min == s)
            printf_z(total, SMALL, &s);
        // else if (min == l)
        //   printf_l(total, LARGE, l, &l);
    }
}

void show_alloc_mem()
{
    UL total;

    total = 0;
    print_zones(&total);
    print_total(total);
}
