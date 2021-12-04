NAME = day02

CC = gcc
CFLAGS += -std=c99 -Wall -Wextra -Wshadow -Werror -pedantic

default: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) -o $(NAME) $(NAME).c

clean: 
	rm -f *.o
	rm -f $(NAME)
