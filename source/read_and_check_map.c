/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:23:16 by shirose           #+#    #+#             */
/*   Updated: 2026/03/28 21:29:55 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int read_and_check_map(char *filename, t_game *game)
{
	if (read_map(filename, game) == -1)
		return (-1);
	if (is_valid_map(game) == -1)
		return (-1);
}