/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:16:45 by shirose           #+#    #+#             */
/*   Updated: 2026/04/15 18:12:46 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_item(t_game *game)
{
	// if (game->move != 0)
	// 	game->map[game->player_y][game->player_x] = '0';

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
			terminate_all(game, 0);
			exit (0);
		}
		else
			ft_putstr_fd("Collect all the items!\n", 1);
	}
}

static void	move_and_print(int x, int y, t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'P')
		game->map[game->player_y][game->player_x] = '0';
	game->player_x += x;
	game->player_y += y;
	ft_putstr_fd("Move count: ", 1);
	ft_putnbr_fd(++game->move, 1);
	ft_putstr_fd("\n", 1);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == 0xff1b)
		terminate_all(game, 0);
	if (keysym == 0xff51 || keysym == 0x0061)
	{
		if (game->map[game->player_y][game->player_x - 1] != '1')
			move_and_print(-1, 0, game);
	}
	else if (keysym == 0xff52 || keysym == 0x0077)
	{
		if (game->map[game->player_y - 1][game->player_x] != '1')
			move_and_print(0, -1, game);
	}
	if (keysym == 0xff53 || keysym == 0x0064)
	{
		if (game->map[game->player_y][game->player_x + 1] != '1')
			move_and_print(1, 0, game);
	}
	if (keysym == 0xff54 || keysym == 0x0073)
	{
		if (game->map[game->player_y + 1][game->player_x] != '1')
			move_and_print(0, 1, game);
	}
	check_item(game);
	// draw_map(game);
	return (0);
}
