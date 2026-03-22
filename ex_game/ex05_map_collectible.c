#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	int		items_collected;
	int		total_items;
	void	*item_img;
	void	*exit_img;
}	t_game;

void	draw_map(t_game *game)
{
	int	x, y;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
										game->floor_img, x * 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
											game->wall_img, x * 32, y * 32);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
											game->exit_img, x * 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
											game->item_img, x * 32, y * 32);
			if (game->player_x == x && game->player_y == y)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
											game->player_img, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

void	check_item(t_game *game)
{
	static int	i = 0;

	printf("CP: check_item 00: i = %d\n", i);
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		printf("CP: check_item 01: i = %d\n", i);
		game->items_collected++;
		printf("CP: check_item 02: i = %d\n", i);
		game->map[game->player_y][game->player_x] = '0';
		printf("Items: %d\n", game->items_collected);
	}

	if (game->map[game->player_y][game->player_x] == 'E')
	{
		if (game->items_collected == game->total_items)
		{
			printf("Game clear!\n");
			exit (0);
		}
		else
			printf("Collect all the items!\n");
	}
	printf("CP: check_item exit: i = %d\n", i++);
}

int handle_keypress(int keysym, t_game *game)
{
	if (keysym == 0xff1b) // ESC
		exit (0);
	if (keysym == 0xff51) // Left
	{
		if (game->map[game->player_y][game->player_x - 1] != '1')
			game->player_x -= 1;
	}
	else if (keysym == 0xff52) // Up
	{
		if (game->map[game->player_y - 1][game->player_x] != '1')
			game->player_y -= 1;
	}
	if (keysym == 0xff53) // Right
	{
		if (game->map[game->player_y][game->player_x + 1] != '1')
			game->player_x += 1;
	}
	if (keysym == 0xff54) // Down
	{
		if (game->map[game->player_y + 1][game->player_x] != '1')
			game->player_y += 1;
	}
	check_item(game);
	draw_map(game);
	return (0);
}

int	main(void)
{
	t_game	game;
	int		img_w, img_h;
	const char 	*src_map[] = {
        "1111111",
        "1000C01",
        "1011101",
        "101E101",
        "1000C01",
		"1111111"
    };

	game.map = malloc(sizeof(char *) * game.map_h);
	game.map_w = 7;
	game.map_h = 6;
	int i = 0;
	while (i < game.map_h)
	{
		game.map[i] = strdup(src_map[i]);
		i++;
	}

	game.player_x = 1;
	game.player_y = 1;
	game.items_collected = 0;
	game.total_items = 2;

	printf("check point 00\n");
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map_w * 32, game.map_h * 32, "map");

	printf("check point 01\n");

	if (game.win_ptr == NULL)
	{
		free(game.mlx_ptr);
		while(--i >= 0)
			free(game.map[i]);
		free(game.map);
		return (1);
	}

	printf("check point 02\n");

	game.floor_img = mlx_xpm_file_to_image(game.mlx_ptr, "floor.xpm", &img_w, &img_h);
	game.wall_img = mlx_xpm_file_to_image(game.mlx_ptr, "wall.xpm", &img_w, &img_h);
	game.player_img = mlx_xpm_file_to_image(game.mlx_ptr, "player.xpm", &img_w, &img_h);
	game.item_img = mlx_xpm_file_to_image(game.mlx_ptr, "coin.xpm", &img_w, &img_h);
	game.exit_img = mlx_xpm_file_to_image(game.mlx_ptr, "exit.xpm", &img_w, &img_h);

	printf("check point 03\n");
	draw_map(&game);

	printf("check point 04\n");
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	
	printf("check point 05\n");
	mlx_loop(game.mlx_ptr);
	return (0);
};