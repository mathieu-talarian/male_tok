NAME= malloc
SRC_PATH= src
SRC_NAME= \
		malloc.c \
		init_env.c \
		set_tiny.c \
		set_small.c \
		tiny_m.c \
		small_m.c\
		large_m.c \
		mmmap.c \
		search_free_chunk.c \
		expand_zone.c \
		free.c \
		defrag.c \
		debug.c \
		realloc.c \
		tiny_realloc.c \
		small_realloc.c \
		realloc_utils.c

OBJ_PATH= obj

IC = -Iincludes

CC = gcc
#CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFTDIR = lib/libft


all: $(NAME)

$(NAME): $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(CFLAGS) $(IC) -o $@ -c $<

test: .libft $(OBJ)
	$(CC) main_test/main.c obj/*.o $(IC) -o malloc -Llib/libft -lft
	./malloc

clean:
	@rm -fv $(OBJ)
	@rmdir -v $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -rfv malloc

.libft:
	make -C $(LIBFTDIR)
.libftclean:
	make clean -C $(LIBFTDIR)
.libftfclean:
	make fclean -C $(LIBFTDIR)

retest: fclean test

re: fclean all
