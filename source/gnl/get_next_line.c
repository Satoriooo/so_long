/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:33:49 by shirose           #+#    #+#             */
/*   Updated: 2026/04/14 17:18:27 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str, ssize_t index)
{
	char	*line;
	ssize_t	i;

	line = malloc(sizeof(char) * (index + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

static char	*get_new_bookmark(char *bm, ssize_t index)
{
	char	*new_bm;
	ssize_t	i;

	new_bm = malloc(ft_strlen(bm) - index);
	if (!new_bm)
		return (NULL);
	i = 0;
	while (bm[index + i + 1] != '\0')
	{
		new_bm[i] = bm[index + i + 1];
		i++;
	}
	new_bm[i] = '\0';
	return (new_bm);
}

static char	*join_and_free(char *bookmark, char *buf)
{
	char	*tmp;

	if (!bookmark)
		bookmark = ft_strdup("");
	if (!bookmark)
		return (NULL);
	tmp = bookmark;
	bookmark = ft_strjoin(tmp, buf);
	free(tmp);
	return (bookmark);
}

static char	*append_buffer(int fd, char *bookmark)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(bookmark), NULL);
	n = 1;
	while (locate_nl(bookmark) == -1 && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(bookmark);
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		bookmark = join_and_free(bookmark, buf);
		if (!bookmark)
			break ;
	}
	free(buf);
	return (bookmark);
}

char	*get_next_line(int fd)
{
	static char	*bookmark;
	char		*line;
	char		*tmp;
	ssize_t		idx;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bookmark = append_buffer(fd, bookmark);
	if (!bookmark)
		return (NULL);
	idx = locate_nl(bookmark);
	if (idx >= 0)
	{
		line = get_line(bookmark, idx);
		if (line == NULL || ft_strlen(line) == 0)
			return(free(bookmark), NULL);
		tmp = bookmark;
		bookmark = get_new_bookmark(bookmark, idx);
		return (free(tmp), line);
	}
	if (!*bookmark)
		return (free(bookmark), bookmark = NULL, NULL);
	line = bookmark;
	return (bookmark = NULL, line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include "get_next_line.h"

// int	main(void)
// {
// 	int		fd = open("sample.txt", O_RDONLY);
// 	char	*line;

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }