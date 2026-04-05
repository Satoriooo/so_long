/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:08 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 13:05:37 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_left(char **map, int cnt)
{
	int i;
	
	if (cnt < 3)
		return (-1);
	i = 0;
	while(i < cnt)
	{
		if (map[i][0] != '1')
		{
			printf("check_left map[%d][0]: %c\n", i, map[i][0]);
			return (-1);
		}
		printf("check_left map line: %s\n", map[i]);
		i++;
	}
	return (0);
}

int	check_top(char **map)
{
	int i;

	i = 0;
	while(map[0][i] && map[0][i] != '\n')
	{
		if (map[0][i] != '1')
			return (printf("return here 01 map[0][%d]: %c\n", i, map[0][i]), -1);
		i++;
	}
	if (i < 3)
		return (printf("Error check top ... not enough columns\n"), -1);
	return (0);
}

int	check_right(char **map, int cnt) // TODO: write on README that the map does not accept a new line at the end
{
	int i;
	int	pre_len;
	int cur_len;

	pre_len = 0;
	i = 0;
	while(i < cnt)
	{
		cur_len = ft_strlen(map[i]);
//		if (pre_len != 0 && pre_len != cur_len && i != cnt - 1)
		if (pre_len != 0 && pre_len != cur_len)
		{
			if (!(i == cnt - 1 && pre_len == cur_len + 1))
				return (printf("return here 00 cur_len: %d, pre_ren: %d\n", cur_len, pre_len), -1);
		}
		if (cur_len < 3 || map[i][cur_len - 2] != '1')
			return (printf("return here 01: cur_len: %d\n", cur_len), -1);
		pre_len = cur_len;
		i++;
	}
	return (0);
}

int	check_bottom(char **map, int cnt)
{
	int	i;

	i = 0;
	cnt--;
	while(map[cnt][i])
	{
		if (map[cnt][i] != '1')
			return (-1);
		printf("map[%d][%d] : %c\n", cnt, i, map[cnt][i]);
		i++;
	}
	return (0);
}

int is_valid_shape(char **map, int cnt)
{
	if (check_left(map, cnt) == -1)
		return (-1);
	if (check_top(map) == -1)
		return (-1);
	if (check_right(map,cnt) == -1)
		return (-1);
	if (check_bottom(map, cnt) == -1)
		return (-1);
	return (0);
}

static void counters_init(t_game *game)
{
	game->exit_on_map = 0;
	game->player_on_map = 0;
	game->items_on_map = 0;
	game->exit_on_path = 0;
	game->items_on_path = 0;
	game->items_collected = 0;
}

int	is_ending_without_nl(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[game->map_h - 1][i])
		i++;
	printf("ending i: %d\n", i);
	if (game->map[game->map_h - 1][i - 1] == '\n')
		return (-1);
	return (0);
}

int is_valid_map(t_game *game)
{
	if (is_ending_without_nl(game) == -1)
	{
		print_error("Map must end without a new line.");
		return (-1);
	}		
	counters_init(game);
	// printf("is_valid_map ... after init game->items_on_path: %d\n", game->items_on_path);
	if (is_valid_shape(game->map, game->map_h) == -1)
	{
		print_error("Map shape is not valid.");
		return (-1);
	}
	if (is_valid_element(game) == -1)
	{
		printf("exit_on_map: %d, player_on_map: %d, items_on_map: %d\n", game->exit_on_map, game->player_on_map, game->items_on_map);
		print_error("Map elements are not valid.");
		return (-1);
	}
	printf("is_valid_map ... player_x: %d\n", game->player_x);
	if (is_valid_path(game) == -1)
	{	
		print_map(game);
		print_error("No valid path on map.");
		printf("game->items_on_map: %d, game->items_on_path: %d\n", game->items_on_map, game->items_on_path);
		printf("game->exit_on_map: %d, game->exit_on_path: %d\n", game->exit_on_map, game->exit_on_path);
		return (-1);
	}
	return (0);
}

