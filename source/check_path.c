/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:58 by shirose           #+#    #+#             */
/*   Updated: 2026/03/29 17:13:32 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_path(t_game *game)
{
	t_counter counter;
	t_point size;
	t_point begin;
	
	game->items_collected = 0;
	game->exit_on_path = 0;
	size.x = game->map_w;
	size.y = game->map_h;
	begin.x = game->player_x;
	begin.y = game->player_y;
	floodfill(game, size, begin);
	if (game->items_on_map != game->items_collected)
		return (-1);
	if (game->exit_on_path != 1)
		return (-1);
}