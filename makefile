NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c philosophers.c utils.c
OBJ = $(SRC:.c=.o)

all: @$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
