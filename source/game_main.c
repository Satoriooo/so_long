/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:48:01 by shirose           #+#    #+#             */
/*   Updated: 2026/04/14 19:42:20 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
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
		}
	}
}

static int	load_images(t_game *game)
{
	game->wall_img = game->wall_img = mlx_xpm_file_to_image
		(game->mlx_ptr, "./textures/wall.xpm", &game->img_w, &game->img_h);
	if (!game->wall_img)
		return (-1);
	game->floor_img = mlx_xpm_file_to_image
		(game->mlx_ptr, "./textures/floor.xpm", &game->img_w, &game->img_h);
	if (!game->floor_img)
		return (-1);
	game->player_img = mlx_xpm_file_to_image
		(game->mlx_ptr, "./textures/player.xpm", &game->img_w, &game->img_h);
	if (!game->player_img)
		return (-1);
	game->item_img = mlx_xpm_file_to_image
		(game->mlx_ptr, "./textures/coin.xpm", &game->img_w, &game->img_h);
	if (!game->item_img)
		return (-1);
	game->exit_img = mlx_xpm_file_to_image
		(game->mlx_ptr, "./textures/exit.xpm", &game->img_w, &game->img_h);
	if (!game->exit_img)
		return (-1);
	return (0);
}

static void	init_mlx_win(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_error("Failed mlx initialization.", game);
	game->win_ptr = mlx_new_window
		(game->mlx_ptr, game->map_w * 32, game->map_h * 32, "map");
	if (!game->win_ptr)
		exit_error("Failed window initialization.", game);
}

static void	init_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->exit_img = NULL;
	game->floor_img = NULL;
	game->item_img = NULL;
	game->player_img = NULL;
	game->wall_img = NULL;
	game->exit_on_map = 0;
	game->exit_on_path = 0;
	game->img_h = 0;
	game->img_w = 0;
	game->items_collected = 0;
	game->items_on_map = 0;
	game->items_on_path = 0;
	game->map = NULL;
	game->map_h = 0;
	game->map_w = 0;
	game->player_on_map = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->move = 0;
	game->error_i = -1;
	game->fd = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	init_struct(&game);
	if (ac != 2)
		exit_error("Invalid number of parameters.", &game);
	else if (read_and_check_map(av[1], &game) == -1)
		exit_error(NULL, &game);
	init_mlx_win(&game);
	if (load_images(&game) == -1)
		exit_error("Failed to load images.", &game);
	draw_map(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, terminate_all, &game);
	mlx_loop(game.mlx_ptr);
	terminate_all(&game, 0);
	return (0);
}
