/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:59:48 by shirose           #+#    #+#             */
/*   Updated: 2026/04/03 20:50:09 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_is_in(char *s, char c)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	printf("invalid letter: %c / ascii %d\n", c, c);
	return (-1);
}

int	is_correct_element(t_game *game)
{
//	printf("exit_on_map: %d, player_on_map: %d, items_on_map: %d\n", game->exit_on_map, game->player_on_map, game->items_on_map);
	if (game->exit_on_map == 1 && game->player_on_map == 1 && game->items_on_map > 0)
		return (0);
	return (-1);
}

int is_valid_element(t_game *game)
{
	int 	i;
	int 	j;

	// p = 1, c > 0, e = 1, and nothing else (other than w('1') & z ('0')).
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if (ft_is_in("PCE10\n", game->map[i][j]) == -1)
				return (-1);
			else if (game->map[i][j] == 'P')
			{
				game->player_x = i;
				game->player_y = j;
				game->player_on_map++;
			}
			else if(game->map[i][j] == 'C')
				game->items_on_map++;
			else if (game->map[i][j] == 'E')
				game->exit_on_map++;
			j++;
		}
		i++;
	}
	if (is_correct_element(game) == 0)
		return (0);
	else
		return (-1);
}
