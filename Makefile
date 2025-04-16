NAME = ft_nm
CFLAGS = -Wall -Wextra -Werror
SRC = main.c
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(LIB):
	make -C libft

%.o:%.c
	cc $(CFLAGS) -c -o $@ $<

clean: 
	make clean -C libft
	rm -f $(OBJ)

fclean: clean 
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
