#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_w;
	int		map_h;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	int		player_x;
	int		player_y;
}	t_game;

