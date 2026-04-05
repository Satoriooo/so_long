/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:07 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 18:58:45 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game *game, t_point size, t_point pos)
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
