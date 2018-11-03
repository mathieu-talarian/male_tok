#include "malloc.h"
#include <stdio.h>

int main(void)
{
    show_alloc_mem();
    ft_malloc(T_MSIZE - 1);
    ft_malloc(S_MSIZE - 1);
    ft_malloc(2332321312313);
    show_alloc_mem();
    return (0);
}
