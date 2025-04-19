NAME = ft_nm
CFLAGS = -Wall -Wextra -Werror
SRC = main.c src/utils.c src/64_files.c src/32_files.c
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(LIB):
	make -C libft

%.o:%.c headers/ft_nm.h
	gcc $(CFLAGS) -c -o $@ $<

clean: 
	make clean -C libft
	rm -f $(OBJ) my_nm_res real_nm_res tester.tmp

fclean: clean 
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
