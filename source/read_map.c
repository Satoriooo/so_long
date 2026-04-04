/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/04 14:02:15 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_map(t_game *game)
{
	int	n;
	
	n = game->map_h;
	while (--n >= 0)
	{
		printf("clean_map map[%d]: %s\n", n, game->map[n]);
		free(game->map[n]);
	}
	free(game->map);
	game->map = NULL;
}

// TODO: Write the definition of correct file name in README
int	is_alpha_num_underbar(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= '0' && s[i] <= '9') || (s[i] == '.' || s[i] == '_')))
			return (-1);
		i++;
	}
	return (0);
}

// TODO: README: filename at least one letter + ".ber" or MAX 100 letters.
int	is_correct_suffix(char *s)
{
	int	i;
	int j;
	char suffix[] = ".ber";
	
	i = 0;
	while(s[i])
		i++;
	if (i < 5 || i > 100)
		return (-1);
	i -= 4;
	j = 0;
	while(s[i] && suffix[j] && s[i] == suffix[j])
	{
		i++;
		j++;
	}
	if (s[i] == suffix[j])
		return (0);
	return (-1);
}

int	is_valid_map_name(char *s)
{
	if (is_alpha_num_underbar(s) == -1)
		return (-1);
	if (is_correct_suffix(s) == -1)
		return (-1);
	return (0);
}

int count_line(char *filename)
{
	char *line;
	int n;
	int	fd;

	fd = open(filename, O_RDONLY);
	n = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		n++;
		free(line);
	}
	close(fd);
	return (n);
}

int	read_map(char *filename, t_game *game)
{
	int		n;
	int 	i;
	int 	fd;
	
	n = is_valid_map_name(filename);
	if (n == -1)
		return (-1);
	n = count_line(filename);
	printf("Result count line: n = %d\n", n);
	game->map = (char **)malloc((sizeof(char *)) * (n + 1));
	if (game->map == NULL)
		return (-1);
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (i < n)
	{
		game->map[i] = get_next_line(fd);
		if (game->map[i] == NULL)
			free(game->map[i]); // TODO: MAKE CLEARNER and free all before alocated stuff if smth failed
		i++;
	}
	game->map[n] = NULL;
	game->map_h = n;
	printf("game->map_h: %d\n", game->map_h);
	game->map_w = ft_strlen(game->map[0]);
	return (0);
}

// int main(int ac, char **av)
// {
// 	char **map;
// 	char filename[] = "map1.ber";

// 	int fd = open(filename, O_RDONLY);

// 	map = read_map(fd, filename);
// 	int i = -1;
// 	while (map[++i] != NULL)
// 		printf("%s", map[i]);
// 	while (i >= 0)
// 		free(map[i--]);
// 	free(map);
// 	close(fd);
// }