NAME = day03

CC = gcc
CFLAGS += -std=c99 -Wall -Wextra -Wshadow -Werror -pedantic
LDLIBS += -lm

default: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(LDLIBS) -o $(NAME) $(NAME).c

clean: 
	rm -f *.o
	rm -f $(NAME)
