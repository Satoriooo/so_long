/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 21:40:41 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_line(char *filename)
{
	char	*line;
	int		n;
	int		fd;

	fd = open(filename, O_RDONLY);
	n = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		n++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (n);
}

int	read_map(int fd, char *filename, t_game *game)
{
	int		n;
	int		i;
	char	*temp;

	n = count_line(filename);
	game->map = (char **)malloc((sizeof(char *)) * (n + 1));
	if (game->map == NULL)
	{
		print_error("malloc for map read failed.");
		return (-1);
	}
	i = 0;
	while (i < n)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	temp = get_next_line(fd);
	free(temp);
	game->map[n] = NULL;
	game->map_h = n;
	game->map_w = ft_strlen(game->map[0]) - 1;
	return (0);
}
