CC = gcc
CFLAGS = -Wall -Werror -Wextra -I.
SRC = ft_bzero.c ft_putnbr_fd.c ft_split.c ft_striteri.c ft_putendl_fd.c ft_putstr_fd.c \
	ft_putchar_fd.c ft_strmapi.c ft_strjoin.c ft_strtrim.c ft_substr.c ft_itoa.c \
	ft_calloc.c ft_strdup.c  ft_atoi.c  ft_isalpha.c  ft_isdigit.c  ft_memchr.c  \
	ft_memcpy.c   ft_memset.c  ft_strlcat.c  ft_strlen.c   ft_strnstr.c  ft_tolower.c \
	ft_isalnum.c  ft_isascii.c  ft_isprint.c  ft_memcmp.c  ft_memmove.c  ft_strchr.c  \
	ft_strlcpy.c  ft_strncmp.c ft_strcmp.c ft_strrchr.c  ft_toupper.c \
	ft_lstnew.c ft_lstiter.c ft_lstmap.c ft_lstclear.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_printfd.c ft_annexes.c \
	get_next_line.c get_next_line_utils.c \
	arg_lst.c argparse.c

NAME = libft.a
OBJETS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJETS)
	ar rc $(NAME) $(OBJETS)

%.o: %.c libft.h ft_printf.h get_next_line.h argparse.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJETS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus 