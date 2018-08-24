#include "malloc.h"
#include <stdio.h>

int main(void)
{
    void *ptr = ft_malloc(12);
    ptr = ft_realloc(ptr, 512);
    ft_free(ptr);
    return (0);
}
