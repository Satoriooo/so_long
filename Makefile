NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Isource/gnl
RM = rm -f

OBJS = source/check_element.o \
	source/check_map.o \
	source/check_path.o \
	source/check_shape.o \
	source/error_handler.o \
	source/game_main.o \
	source/general_util.o \
	source/key_handler.o \
	source/read_and_check_map.o \
	source/read_map.o \
	source/gnl/get_next_line.o \
	source/gnl/get_next_line_utils.o
	
HEAD = so_long.h
GNL_HEAD = source/gnl/get_next_line.h

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm -lmlx -lXext -lX11 -o $(NAME)

source/%.o : source/%.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

source/gnl/%.o: source/gnl/%.c $(GNL_HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
