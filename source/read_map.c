/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 20:27:49 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_map(t_game *game)
{
	int	n;

	n = game->map_h;
	while (--n >= 0)
		free(game->map[n]);
	free(game->map);
	game->map = NULL;
}

int	is_alpha_num_underbar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9') || (s[i] == '.'
					|| s[i] == '_' || s[i] == '/')))
			return (-1);
		i++;
	}
	return (0);
}

int	is_correct_suffix(char *s, char *suffix)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
		i++;
	if (i < 5 || i > 100)
		return (-1);
	i -= 4;
	j = 0;
	while (s[i] && suffix[j] && s[i] == suffix[j])
	{
		i++;
		j++;
	}
	if (s[i] == suffix[j])
		return (0);
	return (-1);
}

void	print_error(char *s)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

int	is_valid_map_name(char *s)
{
	if (is_alpha_num_underbar(s) == -1)
	{
		print_error("Invalid file name. Use [a-z], [A-Z], [0-9], '_', '.'.");
		return (-1);
	}
	if (is_correct_suffix(s, ".ber") == -1)
	{
		print_error("Invalid file suffix. Use '*.ber'");
		return (-1);
	}
	return (0);
}

int	count_line(char *filename)
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
