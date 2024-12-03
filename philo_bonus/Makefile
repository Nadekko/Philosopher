CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 # -fsanitize=memory

NAME = philo_bonus

SRC = main_bonus.c \
	init_struct_bonus.c \
	parsing_bonus.c \
	philo_bonus.c \
	utils_bonus.c \
	utils2_bonus.c \

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