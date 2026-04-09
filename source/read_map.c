/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/09 17:52:02 by shirose          ###   ########.fr       */
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
	if (errno > 0)
	{
		print_error("Count line with gnl failed.");
		close(fd);
		exit(1);
	}
	close(fd);
	return (n);
}

static void	hope_nb_see_this_ugly_func(int fd, t_game *game, int n)
{
	char	*temp;

	temp = get_next_line(fd);
	free(temp);
	game->map[n] = NULL;
	game->map_h = n;
	game->map_w = ft_strlen(game->map[0]) - 1;
}

int	read_map(int fd, char *filename, t_game *game)
{
	int		n;
	int		i;

	n = count_line(filename);
	game->map = (char **)malloc((sizeof(char *)) * (n + 1));
	if (game->map == NULL)
		exit_error("malloc for map read failed.", game);
	i = 0;
	while (i < n)
	{
		game->map[i] = get_next_line(fd);
		if (errno > 0)
		{
			game->error_i = i;
			exit_error("Failed get_next_line.", game);
		}
		i++;
	}
	hope_nb_see_this_ugly_func(fd, game, n);
	return (0);
}
