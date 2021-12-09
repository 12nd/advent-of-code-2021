NAME = day08

CC = gcc
CFLAGS += -std=c99 -Wall -Wextra -Wshadow -Werror -Wconversion -pedantic
LDLIBS += -lm

default: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(LDLIBS) -o $(NAME) $(NAME).c

clean: 
	rm -f *.o
	rm -f $(NAME)
