#include "malloc.h"
#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr;

    addr = ft_malloc(SMALL_MAX_SIZE + 1);
    ft_free((void *) addr + 5);
    // if (ft_realloc((void *) addr + 5, 10) == NULL)
    // 	print("Bonjours\n");
    show_alloc_mem();
}
