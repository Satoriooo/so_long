/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:18:14 by shirose           #+#    #+#             */
/*   Updated: 2026/04/16 18:33:54 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game, int x, int y)
{
	y = -1;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
		{
			if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->floor_img, x * 32, y * 32);
			else if (game->map[y][x] == '1')
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
