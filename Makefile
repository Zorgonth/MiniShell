NAME = minishell

CC = cc

SRC = src/prep.c src/main.c src/tokens.c src/prep2.c \
		src/parsing.c src/red.c src/utils.c src/echo.c \
		src/spl.c src/pwd.c src/cd.c src/env.c src/export.c\
		src/unset.c src/exec.c src/echo2.c src/signals.c\
		src/exit.c src/here_doc.c src/is_built.c\

CFLAGS = -Wall -Werror -Wextra

LINKS = -lreadline

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	cd libft && make
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LINKS)

clean:
	cd libft && make clean
	rm -rf $(OBJ)

fclean: clean
	cd libft && make fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re