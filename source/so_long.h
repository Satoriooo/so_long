#ifndef	SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> // forbidden!
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_w;
	int		map_h;
	int		img_w;
	int		img_h;
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*item_img;
	void	*exit_img;
	int		player_on_map;
	int		player_x;
	int		player_y;
	int		exit_on_map;
	int		exit_on_path;
	int		items_on_map;
	int		items_on_path;
	int		items_collected;
}	t_game;

typedef struct s_elm
{
	int	c;
	int	e;
	int	p;
	int	w;
	int	z;
}	t_elm;

typedef struct s_point {
	int	x;
	int y;
}	t_point;

int		read_and_check_map(char *filename, t_game *game);
void	flood_fill(t_game *game, t_point size, t_point start);
int		read_map(int fd, char *filename, t_game *game);
int		is_valid_map(t_game *game);
int		is_valid_map_name(char *filename);
int		is_valid_path(t_game *game);
int		is_valid_element(t_game *game);
void	clean_map(t_game *game);
void	terminate_all(t_game *game);
void	print_map(t_game *game); // TODO: delete later!
void	exit_error(char *s, t_game *game);
void	print_error(char *s);
void	init_struct(t_game *game);

#endif