#include "malloc.h"

int unmap(void *ptr, size_t size)
{
    munmap(ptr, size);
}

void *map(size_t size)
{
    void *ret;

    if ((ret = mmap(NULL, size, FLAGS, -1, 0)) == MAP_FAILED)
        return (NULL);
    return ret;
}