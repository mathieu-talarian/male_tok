#include "malloc.h"

void *mmmap(size_t size)
{
    void *ret;

    if ((ret = mmap(NULL, size, FLAGS, -1, 0)) == MAP_FAILED)
        return (NULL);
    return ret;
}