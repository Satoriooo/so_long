/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:08 by shirose           #+#    #+#             */
/*   Updated: 2026/04/04 17:46:17 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_left(char **map, int cnt)
{
	int i;

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
	if (i < 3)
		return (-1);
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
		return (printf("return here 02\n"), -1);
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
		if (pre_len != 0 && pre_len != cur_len && i != cnt - 1)
			return (printf("return here 00 cur_len: %d\n", cur_len), -1);
		if (map[i][cur_len - 2] != '1')
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
	int	n;

	n = 0;
	n += check_left(map, cnt);
	printf("left n: %d\n", n);
	n += check_top(map);
	printf("top n: %d\n", n);
	n += check_right(map,cnt);
	printf("right n: %d\n", n);
	n += check_bottom(map, cnt);
	printf("down n: %d\n", n);

	if (n == 0)
		return (0);
	printf("invalid map n: %d\n", n);
	return (-1);
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

int is_valid_map(t_game *game)
{
	
	counters_init(game);
	// printf("is_valid_map ... after init game->items_on_path: %d\n", game->items_on_path);
	if (is_valid_shape(game->map, game->map_h) == -1)
	{
		printf("The shape is NOT valid\n");
		return (-1);
	}
	if (is_valid_element(game) == -1)
	{
		printf("exit_on_map: %d, player_on_map: %d, items_on_map: %d\n", game->exit_on_map, game->player_on_map, game->items_on_map);
		printf("The elements are NOT valid\n");
		return (-1);
	}
	printf("is_valid_map ... player_x: %d\n", game->player_x);
	if (is_valid_path(game) == -1)
	{	
		print_map(game);
		printf("The path is NOT valid\n");
		printf("game->items_on_map: %d, game->items_on_path: %d\n", game->items_on_map, game->items_on_path);
		printf("game->exit_on_map: %d, game->exit_on_path: %d\n", game->exit_on_map, game->exit_on_path);
		return (-1);
	}
	return (0);
}

