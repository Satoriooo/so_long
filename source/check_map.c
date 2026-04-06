/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:08 by shirose           #+#    #+#             */
/*   Updated: 2026/04/06 17:42:34 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_size(t_game *game)
{
	if (game->map_w > 1980 / 32 - 1 || game->map_h > 1080 / 32 - 1)
		return (-1);
	return (0);
}

static int	is_ending_without_nl(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[game->map_h - 1][i])
		i++;
	if (game->map[game->map_h - 1][i - 1] == '\n')
		return (-1);
	return (0);
}

int	is_valid_map(t_game *game)
{
	if (is_valid_size(game) == -1)
		exit_error("Map size is too large. (row < 33, column < 62)", game);
	if (is_ending_without_nl(game) == -1)
	{
		print_error("Map must end without a new line.");
		return (-1);
	}
	if (is_valid_shape(game->map, game->map_h) == -1)
	{
		print_error("Map shape is not valid.");
		return (-1);
	}
	if (is_valid_element(game) == -1)
	{
		print_error("Map elements are not valid.");
		return (-1);
	}
	if (is_valid_path(game) == -1)
	{
		print_error("No valid path on map.");
		return (-1);
	}
	return (0);
}
