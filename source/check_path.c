/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:58 by shirose           #+#    #+#             */
/*   Updated: 2026/04/03 20:42:30 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_path(t_game *game)
{
	t_point size;
	t_point start;
	
	size.x = game->map_w;
	size.y = game->map_h;
	start.x = game->player_x;
	start.y = game->player_y;
	printf("map_h: %d, map_w: %d, player_x: %d, player_y: %d\n", game->map_h, game->map_w, game->player_x, game->player_y);
	// printf("map_h: %d, map_w: %d\n", game->map_h, game->map_w);
	printf("size.x: %d, size.y: %d, start.x: %d, start.y: %d\n", size.x, size.y, start.x, start.y);
	flood_fill(game, size, start);
	if (game->items_on_map != game->items_on_path)
		return (-1);
	if (game->exit_on_path != 1)
		return (-1);
	return (0);
}