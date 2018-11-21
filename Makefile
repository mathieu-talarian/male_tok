# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoullec <mmoullec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/02 20:04:48 by mmoullec          #+#    #+#              #
#    Updated: 2018/11/21 20:41:52 by mmoullec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc_$(HOSTTYPE).so
SRC_PATH= src
SRC_NAME= \
		malloc.c \
		set_zone.c \
		tiny_small_malloc.c \
		large_m.c \
		mmmap.c \
		search_free_chunk.c \
		expand_zone.c \
		free.c \
		defrag.c \
		print_utils.c \
		print_b_utils.c \
		realloc.c \
		tiny_realloc.c \
		small_realloc.c \
		large_r.c \
		realloc_utils.c \
		show_alloc_mem.c \
		export.c

OBJ_PATH= obj

IC = -Iincludes -I$(LIBFTDIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
	$(CC) main_test/main.c obj/*.o $(IC) -o malloc -Llib/libft -lft
	/usr/bin/time -l ./malloc

$(NAME): $(OBJ)
	make -C $(LIBFTDIR)
	ln -F -s $(NAME) libft_malloc.so
	$(CC) $(LDFLAGS) $(LDLIBS) -shared $^ -o $@ -L$(LIBFTDIR) -lft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< $(IC) 

clean:
	@make clean -C $(LIBFTDIR)
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@make fclean -C $(LIBFTDIR)
	@rm -fv $(NAME)
	@rm -fv libft_malloc.so

re : fclean all

.libft:
	make -C $(LIBFTDIR)
.libftclean:
	make clean -C $(LIBFTDIR)
.libftfclean:
	make fclean -C $(LIBFTDIR)

retest: fclean test