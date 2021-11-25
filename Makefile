NAME =		minishell
CC =		clang
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -rf

LIBFT_DIR =	./libft
LIBFT =		$(LIBFT_DIR)/libft.a

SRC_FILES =	minishell.c \
			minipwd.c \
			miniheader.c 

SRC =		$(addprefix src/, $(SRC_FILES))

OBJECTS =	$(SRC:.c=.o)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJECTS) include/minishell.h
			$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJECTS)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libft