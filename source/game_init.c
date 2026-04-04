/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:48:01 by shirose           #+#    #+#             */
/*   Updated: 2026/04/04 15:23:55 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

 // TODO: mpx file must be 32 * 32
void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	printf("--- draw map ----\n\n");
	printf("game->map_h: %d, game->map_w: %d", game->map_h, game->map_w);
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

static void	img_init(t_game *game)
{
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->player_img = NULL;
	game->item_img = NULL;
	game->exit_img = NULL;
	printf("img_init: done\n");
}

int	load_images(t_game *game)
{
	img_init(game);
	game->wall_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/wall.xpm", &game->img_w, &game->img_h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/floor.xpm", &game->img_w, &game->img_h);
	game->player_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/player.xpm", &game->img_w, &game->img_h);
	game->item_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/coin.xpm", &game->img_w, &game->img_h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/exit.xpm", &game->img_w, &game->img_h);
	if (!(game->wall_img) || !(game->floor_img) || !(game->player_img) ||
		!(game->item_img) || !(game->exit_img))
		return (-1);
	printf("load images successful!\n");
	return (0);
}

void	check_item(t_game *game)
{
	static int	i = 0;

	printf("CP: check_item 00: i = %d\n", i);
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		printf("CP: check_item 01: i = %d\n", i);
		(game->items_collected)++;
		printf("CP: check_item 02: i = %d\n", i);
		game->map[game->player_y][game->player_x] = '0';
		printf("Items: %d\n", game->items_collected);
	}

	if (game->map[game->player_y][game->player_x] == 'E')
	{
		if (game->items_collected == game->items_on_map)
		{
			printf("Game clear!\n");
			terminate_all(game);
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
	if (keysym == 0xff51 || keysym == 0x0041) // Left
	{
		if (game->map[game->player_y][game->player_x - 1] != '1')
			game->player_x -= 1;
	}
	else if (keysym == 0xff52 || keysym == 0x0057) // Up
	{
		if (game->map[game->player_y - 1][game->player_x] != '1')
			game->player_y -= 1;
	}
	if (keysym == 0xff53 || keysym == 0x0044) // Right
	{
		if (game->map[game->player_y][game->player_x + 1] != '1')
			game->player_x += 1;
	}
	if (keysym == 0xff54 || keysym == 0x0053) // Down
	{
		if (game->map[game->player_y + 1][game->player_x] != '1')
			game->player_y += 1;
	}
	check_item(game);
	draw_map(game);
	return (0);
}

void error_msg()
{
	printf("Error\n");	
}

int	check_ac(int ac)
{
	if (ac == 2)
		return (0);
	return (-1);
}

int	init_mlx_win(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map_w * 32, game->map_h * 32, "map");
	return (0);
}

void	terminate_all(t_game *game)
{
	clean_map(game);
	if (game->floor_img)
		mlx_destroy_image(game->mlx_ptr, game->floor_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx_ptr, game->exit_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx_ptr, game->player_img);
	if (game->item_img)
		mlx_destroy_image(game->mlx_ptr, game->item_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx_ptr, game->wall_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	printf("terminate_all finished\n");
}

int main(int ac, char **av)
{
	t_game	game;
	int i;

	if (check_ac(ac) == -1)
		return(1);

	if(read_and_check_map(av[1], &game) == -1)
		return(printf("error, read_and_check\n"), 1);

	if (init_mlx_win(&game) == -1)
		return(1);
	printf("check point 01\n");

	i = game.map_h;
	if (game.win_ptr == NULL)
	{
		free(game.mlx_ptr);
		while(--i >= 0)
			free(game.map[i]);
		free(game.map);
		return (printf("error: init_mlx_win\n"),1);
	}

	printf("check point 02\n");

	if (load_images(&game) == -1)
		return (1);
	printf("check point 03\n");
	draw_map(&game);

	printf("check point 04\n");
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	
	printf("check point 05\n");
	mlx_loop(game.mlx_ptr);
	terminate_all(&game);
	exit(0);
	return (0);
};
