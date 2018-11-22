#include "malloc.h"

extern void *malloc(size_t size)
{
    return ft_malloc(size);
}

extern void *realloc(void *ptr, size_t size)
{
    return ft_realloc(ptr, size);
}

extern void free(void *ptr)
{
    return ft_free(ptr);
}

extern void show_alloc_mem()
{
    return ft_show_alloc_mem();
}

extern void *calloc(size_t nb, size_t size)
{
    return ft_calloc(nb, size);
}