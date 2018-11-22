#include "malloc.h"

int main()
{
    for (int i = 0; i < 5; i++)
    {
        void *addr = ft_calloc(12, TINY_MAX_SIZE - 1);
       }
    printf("sadfsadf %zu\n", (SMALL_MAX_SIZE + 1) * 5);
    ft_show_alloc_mem();
    return (0);
}