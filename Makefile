NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Isource/gnl
RM = rm -f

OBJS = source/check_element.o \
	source/check_map.o \
	source/check_path.o \
	source/floodfill.o \
	source/game_init.o \
	source/get_num_nl.o \
	source/read_and_check_map.o \
	source/read_map.o
	source/gnl/get_next_line.o \
	source/gnl/get_next_line_utils.o
HEAD = so_long.h

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

source/%.o : source/%.c $(HEAD)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

source/gnl/%.o: source/gnl/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

source/gnl/get_next_line.o source/gnl/get_next_line_utils.o: source/gnl/get_next_line.h

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re