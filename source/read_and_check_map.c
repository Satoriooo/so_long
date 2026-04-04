/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:23:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/04 20:34:03 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	read_and_check_map(char *filename, t_game *game)
{
	int	fd;
	
	if (is_valid_map_name(filename) == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read_map(fd, filename, game) == -1)
		return (-1);
	if (is_valid_map(game) == -1)
	{
		printf("is_valid_map .... nope!\n");
		return (-1);
	}
	clean_map(game);
	read_map(fd, filename, game);
	return (0);
}
