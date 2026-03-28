/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:43 by shirose           #+#    #+#             */
/*   Updated: 2026/03/28 19:01:45 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_line(int fd)
{
	char *line;
	int n;

	n = 0;
	while ((line = get_next_line(fd)) != NULL)
		n++;
	close(fd);
	return (n);
}

char **read_map(int fd, char *filename)
{
	int n;
	int i;
	char *line;
	char **map;

	n = count_line(fd);
	open(filename, O_RDONLY);
	map = (char **)malloc((sizeof(char *)) * n + 1);
	i = 0;

	while (i < n)
	{
		line = get_next_line(fd);
		printf("read_map check 00 line: %s\n", line);
		map[i] = ft_strdup(line);
		free((char *)line);
		i++;
	}
	map[n] = NULL;

	return (map);
}

int main()
{
	char **map;
	char filename[] = "map1.ber";

	int fd = open(filename, O_RDONLY);

	map = read_map(fd, filename);
	int i = -1;
	while (map[++i] != NULL)
		printf("%s", map[i]);
	while (i >= 0)
		free(map[i--]);
	free(map);
	close(fd);
}