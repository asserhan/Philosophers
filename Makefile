 NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -g #-fsanitize=thread
RM = rm -f
SRC = mandatory/parsing.c mandatory/init.c mandatory/philo.c mandatory/utils.c mandatory/main.c
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
