/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:32:37 by shirose           #+#    #+#             */
/*   Updated: 2026/04/06 17:43:21 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "get_next_line.h"

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
	int		move;
}	t_game;

typedef struct s_elm
{
	int	c;
	int	e;
	int	p;
	int	w;
	int	z;
}	t_elm;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int		read_and_check_map(char *filename, t_game *game);
int		read_map(int fd, char *filename, t_game *game);
int		handle_keypress(int keysym, t_game *game);
int		is_valid_map(t_game *game);
int		is_valid_shape(char **map, int cnt);
int		is_valid_path(t_game *game);
int		is_valid_element(t_game *game);
void	exit_error(char *s, t_game *game);
void	clean_map(t_game *game);
int		terminate_all(t_game *game, int n);
void	exit_error(char *s, t_game *game);
void	print_error(char *s);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	draw_map(t_game *game);

#endif
