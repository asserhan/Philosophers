 NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
RM = rm -f
SRC = parsing.c utils_2.c init.c philo.c utils.c main.c
OBJ = $(SRC:.c=.o)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean
