/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:48:01 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 18:47:21 by shirose          ###   ########.fr       */
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

int	load_images(t_game *game)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/wall.xpm", &game->img_w, &game->img_h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/floor.xpm", &game->img_w, &game->img_h);
	game->player_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/player.xpm", &game->img_w, &game->img_h);
	game->item_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/coin.xpm", &game->img_w, &game->img_h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx_ptr, "./image/exit.xpm", &game->img_w, &game->img_h);
	if (!(game->wall_img) || !(game->floor_img) || !(game->player_img) ||
		!(game->item_img) || !(game->exit_img))
		return (-1);
	return (0);
}

void	check_item(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		game->items_collected++;
		game->map[game->player_y][game->player_x] = '0';
	}

	if (game->map[game->player_y][game->player_x] == 'E')
	{
		if (game->items_collected == game->items_on_map)
		{
			ft_putstr_fd("Game clear!\n", 1);
			terminate_all(game);
			exit (0);
		}
		else
			ft_putstr_fd("Collect all the items!\n", 1);
	}
}

void	move_and_print(int x, int y, t_game *game)
{
	game->player_x += x;
	game->player_y += y;
	ft_putstr_fd("Move count: ", 1);
	ft_putnbr_fd(++game->move, 1);
	ft_putstr_fd("\n", 1);
}

int handle_keypress(int keysym, t_game *game)
{
	if (keysym == 0xff1b) // ESC
		terminate_all(game);
	if (keysym == 0xff51 || keysym == 0x0041) // Left
	{
		if (game->map[game->player_y][game->player_x - 1] != '1')
			move_and_print(-1, 0, game);
	}
	else if (keysym == 0xff52 || keysym == 0x0057) // Up
	{
		if (game->map[game->player_y - 1][game->player_x] != '1')
			move_and_print(0, -1, game);
	}
	if (keysym == 0xff53 || keysym == 0x0044) // Right
	{
		if (game->map[game->player_y][game->player_x + 1] != '1')
			move_and_print(1, 0, game);
	}
	if (keysym == 0xff54 || keysym == 0x0053) // Down
	{
		if (game->map[game->player_y + 1][game->player_x] != '1')
			move_and_print(0, 1, game);
	}
	check_item(game);
	draw_map(game);
	return (0);
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
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map_w * 32,
		game->map_h * 32, "map");
	return (0);
}

int	terminate_all(t_game *game)
{
	if (game->map)
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
	exit(1);
}

void	exit_error(char *s, t_game *game)
{
	if (s)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
	if (game->map)
		clean_map(game);
	if (game)
		terminate_all(game);
}

void	init_struct(t_game *game)
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
}

int main(int ac, char **av)
{
	t_game	game;

	init_struct(&game);
	if (check_ac(ac) == -1)
	exit_error("Invalid number of parameters.", &game);
	else if(read_and_check_map(av[1], &game) == -1)
	exit_error(NULL, &game);
	else if (init_mlx_win(&game) == -1)
	exit_error("Failed to initialize MLX window.", &game);
	if (load_images(&game) == -1)
	exit_error("Failed to load images.", &game);
	draw_map(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, terminate_all, &game);	
	mlx_loop(game.mlx_ptr);
	terminate_all(&game);
	exit(0);
	return (0);
};
