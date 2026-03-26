NAME    = my_project
CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror -I ./get_next_line

SRCS    = read_map.c \
          get_next_line/get_next_line.c \
          get_next_line/get_next_line_utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all