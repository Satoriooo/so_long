/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:00:08 by shirose           #+#    #+#             */
/*   Updated: 2026/03/29 17:08:18 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_strlen(char *s)
{
	int n;
	
	n = 0;
	while (s[n])
		n++;
	return (n);
}

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

int	check_top(char **map, int cnt)
{
	int i;

	i = 0;
	while(map[0][i])
	{
		if (map[0][i] != '1')
			return (-1);
		i++;
	}
	if (i < 3)
		return (-1);
	return (0);
}

int	check_right(char **map, int cnt)
{
	int i;
	int	pre_len;
	int cur_len;

	pre_len = 0;
	i = 0;
	while(i < cnt)
	{
		cur_len = ft_strlen(map[i]);
		if (pre_len != 0 && pre_len != cur_len)
			return (-1);
		if (map[i][cur_len - 1] != '1')
			return (-1);
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
	n += check_top(map,cnt);
	n += check_right(map,cnt);
	n += check_bottom(map, cnt);

	if (n == 4)
		return (0);
	printf("invalid map\n");
	return (-1);
}

int is_valid_map(t_game *game)
{
	t_point begin;
	t_point size;

	if (is_valid_shape(game->map, game->map_h) == -1)
	{
		printf("The shape is NOT valid\n");
		return (-1);
	}
	if (is_valid_element(game->map, game->map_h) == -1)
	{
		printf("The elements are NOT valid\n");
		return (-1);
	}
	if (is_valid_path(game) == -1)
		// TODO:
		// It checks...
			// - if theres only (0, 1, P, E, C)
			// - if there's only one (P, E) on the entire map
			// - if there are all of C in floodfill area
			// - '0' can remain left out side of floodfill area
			
		printf("The path is valid\n");
	else
		printf("The path is NOT valid\n");

}
