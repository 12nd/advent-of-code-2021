NAME = day21

CC = gcc
CFLAGS += -std=c99 -Wall -Wextra -Wshadow -Werror -Wconversion -pedantic -g
LDLIBS += -lm

default: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(LDLIBS) -o $(NAME) $(NAME).c

clean: 
	rm -f *.o
	rm -f $(NAME)
