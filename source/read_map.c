/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/16 20:55:35 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_line(char *filename, t_game *game)
{
	char	*line;
	int		n;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Open failed.", game);
	n = 0;
	errno = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		n++;
		free(line);
		line = get_next_line(fd);
	}
	if (errno > 0)
		exit_error("Count line with gnl failed.", game);
	close(fd);
	return (n);
}

static void	hope_nb_see_this_ugly_func(t_game *game, int n)
{
	game->map[n] = NULL;
	game->map_h = n;
	game->map_w = ft_strlen(game->map[0]) - 1;
}

int	read_map(int fd, char *filename, t_game *game)
{
	int		n;
	int		i;

	n = count_line(filename, game);
	if (n == 0)
		exit_error("Map is empty.", game);
	game->map = (char **)malloc((sizeof(char *)) * (n + 1));
	if (game->map == NULL)
		exit_error("malloc for map read failed.", game);
	i = 0;
	while (i < n)
	{
		errno = 0;
		game->map[i] = get_next_line(fd);
		if (errno > 0)
		{
			game->error_i = i;
			exit_error("Failed get_next_line.", game);
		}
		i++;
	}
	hope_nb_see_this_ugly_func(game, n);
	return (0);
}
