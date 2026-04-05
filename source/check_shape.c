/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:51:53 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 21:20:06 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_left(char **map, int cnt)
{
	int	i;

	if (cnt < 3)
		return (-1);
	i = 0;
	while (i < cnt)
	{
		if (map[i][0] != '1')
			return (-1);
		i++;
	}
	return (0);
}

static int	check_top(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] && map[0][i] != '\n')
	{
		if (map[0][i] != '1')
			return (-1);
		i++;
	}
	if (i < 3)
		return (-1);
	return (0);
}

static int	check_right(char **map, int cnt)
{
	int	i;
	int	pre_len;
	int	cur_len;

	pre_len = 0;
	i = 0;
	while (i < cnt)
	{
		cur_len = ft_strlen(map[i]);
		if (pre_len != 0 && pre_len != cur_len)
		{
			if (!(i == cnt - 1 && pre_len == cur_len + 1))
				return (-1);
		}
		if (cur_len < 3 || map[i][cur_len - 2] != '1')
			return (-1);
		pre_len = cur_len;
		i++;
	}
	return (0);
}

static int	check_bottom(char **map, int cnt)
{
	int	i;

	i = 0;
	cnt--;
	while (map[cnt][i])
	{
		if (map[cnt][i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	is_valid_shape(char **map, int cnt)
{
	if (check_left(map, cnt) == -1)
		return (-1);
	if (check_top(map) == -1)
		return (-1);
	if (check_right(map, cnt) == -1)
		return (-1);
	if (check_bottom(map, cnt) == -1)
		return (-1);
	return (0);
}
