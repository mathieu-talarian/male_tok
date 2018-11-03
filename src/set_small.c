#include "malloc.h"

static size_t set_small_zone() {
  size_t q;
  size_t r;
  size_t size;

  q = S_RSIZE / PS;
  r = (S_RSIZE % PS) ? 1 : 0;
  size = (q + r) * PS;
  while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_chunk)) < 100)
    size += PS;
  return (size);
}

void *set_small() {
  t_zone *zone;
  size_t size;

  size = set_small_zone();
  if ((zone = map(size)) != NULL) {
    zone->next = NULL;
    zone->previous = NULL;
    zone->head = (void *)(zone + 1);
    zone->head->size = size - sizeof(t_zone) - sizeof(t_chunk);
    zone->head->free = 0;
    FREE_IT(zone->head->free);
    zone->head->next = NULL;
    zone->head->previous = NULL;
    zone->tail = zone->head;
    return (void *)zone;
  }
  return (NULL);
}