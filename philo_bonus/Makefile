CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 # -fsanitize=memory

NAME = philo_bonus

SRC = main.c \
	init_struct.c \
	parsing.c \
	philo.c \
	utils.c \
	utils2.c \

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