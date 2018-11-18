#include "malloc.h"

void defrag(t_chunk *chunk)
{
    if ((chunk->previous && chunk->previous->free) ||
        (chunk->next && chunk->next->free))
    // do defrag() with call to defrag forgot the word;
    {
    }
    return;
}
