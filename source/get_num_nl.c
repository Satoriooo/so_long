/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_nl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:26 by shirose           #+#    #+#             */
/*   Updated: 2026/04/05 18:52:32 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_nl(int fd)
{
	char	*line;
	int		n;

	n = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		n++;
	}
	return (n);
}
