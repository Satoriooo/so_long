NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = ft_split.c \
	general_utils.c \
	main.c \
	list_operation.c \
	parse_handler.c \
	ps_operation.c \
	ps_utils.c \
	ps_utils2.c \
	sort_radix.c \
	sort_manual.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

%.o : %.c push_swap.h
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re