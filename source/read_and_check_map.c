/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:23:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 21:41:12 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_alpha_num_underbar(char *s)
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

static int	is_correct_suffix(char *s, char *suffix)
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

static int	is_valid_map_name(char *s)
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

static int	open_file(char *filename)
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
