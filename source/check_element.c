/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:59:48 by shirose           #+#    #+#             */
/*   Updated: 2026/03/30 16:44:33 by shirose          ###   ########.fr       */
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
	return (-1);
}

int	is_correct_element(t_game *game)
{
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
			if (ft_is_in("PCE10", game->map[i][j]) == 0)
				return (-1);
			else if (game->map[i][j] == 'P')
				game->player_on_map++;
			else if(game->map[i][j] == 'C')
				game->items_on_map++;
			else if (game->map[i][j] == 'E')
				game->exit_on_map++;
			j++;
		}
		i++;
	}
	if (is_correct_element(game) == 1)
		return (0);
	else
		return (-1);
}
