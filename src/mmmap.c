#include "malloc.h"

int unmap(void *ptr, size_t size)
{
    return munmap(ptr, size);
}

void *map(size_t size)
{
  static int i = 0;
  printf("Map %d | size = %zu \n", i++, size);
    void *ret;

    if ((ret = mmap(NULL, size, FLAGS, -1, 0)) == MAP_FAILED)
        return (NULL);
    return ret;
}