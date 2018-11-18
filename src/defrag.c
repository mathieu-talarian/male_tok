#include "malloc.h"

void defrag(t_chunk *chunk)
{
    if ((chunk->previous && IS_FREE(chunk->previous->free)) ||
        (chunk->next && IS_FREE(chunk->next->free)))
    // do defrag() with call to defrag forgot the word;
    {
    }
    return;
}
