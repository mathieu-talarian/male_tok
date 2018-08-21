NAME= malloc
SRC_PATH= src
SRC_NAME= malloc.c \
		init_env.c

OBJ_PATH= obj

IC = -Iincludes

CC = gcc
#CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))


all: $(NAME)

$(NAME): $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(CFLAGS) $(IC) -o $@ -c $<

test: .libft $(OBJ) 
	$(CC) main_test/main.c obj/*.o $(IC) -o malloc
	./malloc

clean:
	@rm -fv $(OBJ)
	@rmdir -v $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -rfv malloc

.libft: 
	make -C libft
.libftclean:
	make clean -C libft
.libftfclean:
	make fclean -C libft

retest: fclean test

re: fclean all