CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= philo
SRC		= main.c ft_atoi.c ft_putstr_fd.c time.c argv.c

all: $(NAME)

$(NAME): $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all