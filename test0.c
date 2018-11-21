#include "malloc.h"

int main()
{
    for (int i = 0; i < 5; i++)
    {
        void *addr = ft_malloc(SMALL_MAX_SIZE - 1);
        ft_free(addr);
    }
    printf("sadfsadf %zu\n", (SMALL_MAX_SIZE + 1) * 5 );
    ft_show_alloc_mem();
    return (0);
}