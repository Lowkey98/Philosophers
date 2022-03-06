CC		= gcc
CFLAGS	= -Wall -Werror -Wextra  #-fsanitize=thread -g
NAME	= philo
SRC		= philo.c free.c data.c main.c utils.c time.c argv.c

all: $(NAME)

$(NAME): $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all