/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:59:48 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 18:33:01 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int ft_is_in(char *s, char c)
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

static int	is_correct_element(t_game *game)
{
	if (game->exit_on_map == 1 && game->player_on_map == 1 && game->items_on_map > 0)
		return (0);
	return (-1);
}

static void	set_player_pos(t_game *game, int x, int y)
{	
	game->player_x = x;
	game->player_y = y;
	game->player_on_map++;
}

int	is_valid_element(t_game *game)
{
	int 	i;
	int 	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if (ft_is_in("PCE10\n", game->map[i][j]) == -1)
				return (-1);
			else if (game->map[i][j] == 'P')
				set_player_pos(game, i, j);
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
