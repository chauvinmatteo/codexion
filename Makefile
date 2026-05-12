CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = ./src/parsing.c ./src/init.c ./src/coders.c ./src/utils.c ./src/codexion.c
OBJS = $(SRCS:.c=.o)
NAME = codexion
INCLUDES = -I./include

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re