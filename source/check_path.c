/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:58 by shirose           #+#    #+#             */
/*   Updated: 2026/04/07 17:33:39 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(t_game *game, t_point size, t_point pos)
{
	t_point		p;

	p = pos;
	if (p.x < 0 || p.x > size.x - 1 || p.y < 0 || p.y > size.y - 1)
		return ;
	if (game->map[p.y][p.x] == 'F' || game->map[p.y][p.x] == '1')
		return ;
	if (game->map[p.y][p.x] == 'C')
		game->items_on_path++;
	if (game->map[p.y][p.x] == 'E')
		game->exit_on_path++;
	game->map[p.y][p.x] = 'F';
	p.x--;
	flood_fill(game, size, p);
	p.x++;
	p.y--;
	flood_fill(game, size, p);
	p.y++;
	p.x++;
	flood_fill(game, size, p);
	p.x--;
	p.y++;
	flood_fill(game, size, p);
}

int	is_valid_path(t_game *game)
{
	t_point	size;
	t_point	start;

	size.x = game->map_w;
	size.y = game->map_h;
	start.x = game->player_x;
	start.y = game->player_y;
	flood_fill(game, size, start);
	if (game->items_on_map != game->items_on_path)
		return (-1);
	if (game->exit_on_path != 1)
		return (-1);
	return (0);
}
