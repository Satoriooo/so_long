/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:57:30 by shirose           #+#    #+#             */
/*   Updated: 2026/04/09 17:34:43 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error(char *s)
{
	if (s)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	exit_error(char *s, t_game *game)
{
	if (game->fd > 0)
	{
		close(game->fd);
		game->fd = -1;
	}
	print_error(s);
	if (game->map)
		clean_map(game);
	if (game)
		terminate_all(game, 1);
}
