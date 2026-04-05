/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:23:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 20:34:59 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("File does not exist, or no read permission.");
	return (fd);
}

int	read_and_check_map(char *filename, t_game *game)
{
	int	fd;

	if (is_valid_map_name(filename) == -1)
		return (-1);
	fd = open_file(filename);
	if (fd == -1)
		return (-1);
	if (read_map(fd, filename, game) == -1)
		return (-1);
	if (is_valid_map(game) == -1)
		return (-1);
	clean_map(game);
	close(fd);
	fd = open_file(filename);
	if (fd == -1)
		return (-1);
	read_map(fd, filename, game);
	return (0);
}
