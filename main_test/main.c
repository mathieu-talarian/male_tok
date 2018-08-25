#include "malloc.h"
#include <stdio.h>

int main(void)
{
    void *ptr = ft_malloc(513);
    ptr = ft_realloc(ptr, 517);
    ft_free(ptr);
    return (0);
}
