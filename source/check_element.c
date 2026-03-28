/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:59:48 by shirose           #+#    #+#             */
/*   Updated: 2026/03/28 18:59:58 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_is_in(char *s, char c)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_elm_correct(t_elm *elm)
{
	if (elm->p == 1 &&
		elm->e == 1 &&
		elm->c > 0)
		return (1);
	return (0);
}

int is_element_valid(char **map)
{
	int 	i;
	int 	j;
	t_elm	elm;

	elm.p = 0;
	elm.c = 0;
	elm.e = 0;

	// p = 1, c > 0, e = 1, and nothing else (other than w('1') & z ('0')).
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (ft_is_in("PCE10", map[i][j]) == 0)
				return (0);
			else if (map[i][j] == 'P')
				elm.p++;
			else if(map[i][j] == 'C')
				elm.c++;
			else if (map[i][j] == 'E')
				elm.e++;
			j++;
		}
		i++;
	}
	if (is_elm_correct(&elm) == 1)
		return (1);
	else
		return (0);
}
