# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/02 20:04:48 by mmoullec          #+#    #+#              #
#    Updated: 2018/11/03 12:03:11 by mmoullec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= malloc
SRC_PATH= src
SRC_NAME= \
		malloc.c \
		init_env.c \
		set_zone.c \
		tiny_small_malloc.c \
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
		large_r.c \
		realloc_utils.c \
		show_alloc_mem.c

OBJ_PATH= obj

IC = -Iincludes

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFTDIR = lib/libft


all: $(NAME)

$(NAME): $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(CFLAGS) $(OFLAGS) $(IC) -o $@ -c $<

test: .libft $(OBJ)
	$(CC) $(CFLAGS) $(OFLAGS) main_test/main.c obj/*.o $(IC) -o malloc -Llib/libft -lft
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
