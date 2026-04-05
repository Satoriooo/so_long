/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 13:16:42 by shirose          ###   ########.fr       */
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
			(s[i] >= '0' && s[i] <= '9') || (s[i] == '.' || s[i] == '_' || s[i] == '/')))
		{
			printf("error with this letter: c = %c\n", s[i]);
			return (-1);
		}
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

void	print_error(char *s)
{
	write(2, "Error:\n", 7);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

int	is_valid_map_name(char *s)
{
	if (is_alpha_num_underbar(s) == -1)
	{
		print_error("Invalid file name. Use [a-z], [A-Z], [0-9], '_', '.'.");
		return (-1);
	}
	if (is_correct_suffix(s) == -1)
	{
		print_error("Invalid file suffix. Use '*.ber'");
		return (-1);
	}
	return (0);
}

int count_line(char *filename)
{
	char	*line;
	int 	n;
	int		fd;

	fd = open(filename, O_RDONLY);
	n = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line: %s\n", line);
		n++;
		free(line);
	}
	close(fd);
	return (n);
}

int	read_map(int fd, char *filename, t_game *game)
{
	int		n;
	int 	i;
	char 	*temp;
	
	n = count_line(filename);
	printf("Result count line: n = %d\n", n);
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
	printf("game->map_h: %d\n", game->map_h);
	game->map_w = ft_strlen(game->map[0]) - 1;
	printf("game map: %s\n", game->map[0]);
	printf("game->map_w: %d\n", game->map_w);
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