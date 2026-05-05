CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = 
OBJS = $(SRCS:.c=.o)
NAME = codexion

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re