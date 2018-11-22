#include "malloc.h"

int main()
{
    void *addr = NULL;
    for (int i = 0; i < 5; i++)
    {
        addr = ft_realloc(addr, 15 * i);
    }
    printf("sadfsadf %zu\n", (SMALL_MAX_SIZE + 1) * 5);
    ft_show_alloc_mem();
    return (0);
}