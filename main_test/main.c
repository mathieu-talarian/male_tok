#include "malloc.h"
#include <stdio.h>

int main(void)
{
    void *ptr = ft_malloc(12);
    ft_malloc(513);
    ft_malloc(15361);
    ft_free(ptr);
    return (0);
}
