#include "malloc.h"

void *ft_realloc(void *ptr, size_t size) {
  t_chunk *chunk;
  void *addr;

  addr = NULL;
  if (!ptr)
    return MALLOC(size);
  if (!size) {
    FREE(ptr);
    return NULL;
  }
  chunk = ((t_chunk *)ptr - 1);
  if ((addr = tiny_realloc(ptr, chunk, size)))
    ;
  else if ((addr = small_realloc(ptr, chunk, size)))
    ;
  else if ((addr = large_realloc(ptr, chunk, size)))
    ;
  return (addr);
}
