#include "malloc.h"
#include <stdio.h>

int main(void)
{
    void *ptr = ft_malloc(12);
    ptr = ft_realloc(ptr, 15);
    ft_malloc(513);
    ft_malloc(15361);
    ft_free(ptr);
    return (0);
}
