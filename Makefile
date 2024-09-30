CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -pthread

NAME = philo

SRC = main.c \
	parsing.c \
	init_struct.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re