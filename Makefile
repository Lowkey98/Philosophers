CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= philo
SRC		= main.c

all: $(NAME)

$(NAME): $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all