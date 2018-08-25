#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

#include "../lib/libft/libft.h"

#define MALLOC(x) ft_malloc(x)
#define FREE(x) ft_free(x)
#define REALLOC ft_realloc

#define T_RSIZE 256 * 4096 // 512 * pagesize
#define T_MSIZE 512        // tiny Maxsize

#define S_RSIZE 2048 * 4096 //
#define S_MSIZE 15360       // small Maxsize

#define TINY 0
#define SMALL 1
#define LARGE 2

#define UL unsigned long long

#define DEBUG_MASK (1 << 3)
#define DEBUG_ON(x) (x |= DEBUG_MASK)
#define DEBUG_OFF(x) (x ^= DEBUG_MASK)
#define IS_DEBUG(x) (x & DEBUG_MASK ? 1 : 0)
#define D IS_DEBUG(g_env.env)

#define E g_env
#define Z t_zone
#define PS g_env.pagesize

#define FLAGS PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE

#define FREE_MASK (1 << 2)
#define FREE_IT(x) (x |= FREE_MASK)
#define UNFREE_IT(x) (x ^= FREE_MASK)
#define IS_FREE(x) (x & FREE_MASK ? 1 : 0)
struct s_chunk
{
    size_t size;
    char free;
    struct s_chunk *next;
    struct s_chunk *previous;
};

typedef struct s_chunk t_chunk;

struct s_zone
{
    t_chunk *head;
    t_chunk *tail;
    struct s_zone *previous;
    struct s_zone *next;
};
typedef struct s_zone t_zone;

typedef void *(*t_f)(size_t);

struct s_env
{
    char env;
    size_t pagesize;
    t_zone *tiny;
    t_zone *small;
    t_chunk *large;
    t_f func_m[3];
};
typedef struct s_env t_env;

extern int g_cpt[3];
extern t_env g_env;

void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_free(void *ptr);

int init_env();
void *set_tiny();
void *set_small();

void *map(size_t size);
int unmap(void *ptr, size_t size);

void *tiny_m(size_t size);
void *small_m(size_t size);
void *large_m(size_t size);

void *search_free_chunk(t_zone *zone, int type, size_t size);
void *expand_zone(t_zone *zone, int type, size_t size);
void *split_block(t_zone *cz, t_chunk *cc, int t, size_t size);
void *fusion_block(t_zone *cz, t_chunk *cc, int t, size_t size);

int in_chunk(t_chunk *z_head, t_chunk *searched_chunk);

// REALLOC
void *tiny_realloc(void *ptr, t_chunk *chunk, size_t size);
void *small_realloc(void *ptr, t_chunk *chunk, size_t size);
void *large_realloc(void *ptr, t_chunk *chunk, size_t size);

size_t have_enough_space(t_chunk *chunk, size_t size);

void *find_zone(t_zone *head, t_chunk *searched);
void *find_chunk(t_chunk *head, t_chunk *searched);
void *move_and_free(void *ptr, size_t chunk_size, size_t size);

void show_alloc_mem();

void defrag();

int debug();
#endif
