#include "malloc.h"

extern void *malloc(size_t size) {
    return ft_malloc(size);
}