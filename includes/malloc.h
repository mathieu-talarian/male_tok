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

#define T_RSIZE 1048576
#define T_MSIZE 512 // tiny Maxsize

#define S_RSIZE 8388608
#define S_MSIZE 15360 // small Maxsize

#define TINY 1
#define SMALL 2
#define LARGE 3

#define E g_env
#define Z t_zone
#define PS g_env.pagesize

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

struct s_env
{
    size_t pagesize;
    t_zone *tiny;
    t_zone *small;
    t_chunk *large;
};
typedef struct s_env t_env;

extern t_env g_env;

void *ft_malloc(size_t size);
int init_env();

#endif