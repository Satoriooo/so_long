#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_w;
	int		map_h;
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	int		player_x;
	int		player_y;
}	t_game;

void	draw_map(t_game *game)
{
	int	x, y;

	y = 0;
	while(y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
									game->floor_img, x * 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
										game->wall_img, x * 32, y * 32);
			if (y == game->player_y && x == game->player_x)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
										game->player_img, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

int handle_keypress(int keysym, t_game *game)
{
	if (keysym == 65307) // ESC
		exit (0);
	
	if (keysym == 65361) // Left
	{
		if (game->map[game->player_y][game->player_x - 1] != '1')
			game->player_x -= 1;
	}
	else if (keysym == 65362) // Up
	{
		if (game->map[game->player_y - 1][game->player_x] != '1')
			game->player_y -= 1;
	}
	else if (keysym == 65363) // Right
	{
		if (game->map[game->player_y][game->player_x + 1] != '1')
			game->player_x += 1;
	}
	else if (keysym == 65364) // Down
	{
		if (game->map[game->player_y + 1][game->player_x] != '1')
			game->player_y+= 1;
	}
	draw_map(game);
	return (0);
}

int main(void)
{
	t_game	game;
	int img_w, img_h;

char *temp_map[] = {
        "1111111",
        "1000001",
        "1011101",
        "1000001",
        "1111111"
    };

	game.map = temp_map;
	game.map_w = 7;
	game.map_h = 5;
	game.player_x = 1;
	game.player_y = 1;

	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map_w * 32, game.map_h * 32, "map");
	if (game.win_ptr == NULL)
	{
		free(game.mlx_ptr);
		return (1); 
	}
	game.wall_img = mlx_xpm_file_to_image(game.mlx_ptr, "wall.xpm", &img_w, &img_h);
	game.player_img = mlx_xpm_file_to_image(game.mlx_ptr, "player.xpm", &img_w, &img_h);
	game.floor_img = mlx_xpm_file_to_image(game.mlx_ptr, "floor.xpm", &img_w, &img_h);

	draw_map(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}