/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:01:07 by shirose           #+#    #+#             */
/*   Updated: 2026/04/04 18:02:00 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// fllodfill ... check map -> count and save in counter
void	flood_fill(t_game *game, t_point size, t_point pos)
{
	t_point		p;
	static int	cnt = 0;

	cnt++;
	p = pos;
	
	printf("floodfill called: cnt = %d, (y, x) = (%d, %d)\n", cnt, p.y, p.x);

	// check if the current position is valid
	if (p.x < 0 || p.x > size.x - 1 || p.y < 0 || p.y > size.y - 1)
	{
		printf("Return point 01\n");
		return ;
	}
	// If its wall or 'F', do nothing and return
	if (game->map[p.y][p.x] == 'F' || game->map[p.y][p.x] == '1')
	{
		printf("Return point 02\n");
		return ;
	}
	if (game->map[p.y][p.x] == 'C')
	{
		(game->items_on_path)++;
		printf("found item on path! (y, x) = (%d, %d)\n", p.y, p.x);
		printf("game->items_on_path: %d --- e: %d\n", game->items_on_path, game->exit_on_path);
	}
	if (game->map[p.y][p.x] == 'E')
		(game->exit_on_path)++;

	game->map[p.y][p.x] = 'F';
	if (cnt > 100000)
		return ;

	p.x--;
	flood_fill(game, size, p); // Left !!!
	p.x++;
	p.y--;
	flood_fill(game, size, p); //Up
	p.y++;
	p.x++;
	flood_fill(game, size, p); // Right
	p.x--;
	p.y++;
	flood_fill(game, size, p); // Down
}

// char **make_area(char **zone, t_point size)
// {
// 	int		i;
// 	int		j;
// 	char	**c;

// 	printf("size.y: %d\n", size.y);
// 	c = (char **)malloc(sizeof(char *) * (size.y + 1));
// 	i = 0;
// 	while(i < size.y)
// 	{
// 		printf("make_area i: %d\n", i);
// 		c[i] = (char *)malloc(sizeof(char) * (size.x + 1));
// 		j = 0;
// 		while (j < size.x)
// 		{
// 			c[i][j] = zone[i][j];
// 			j++;
// 		}
// 		c[i][j] = '\0';
// 		i++;
// 	}
// 	c[i] = NULL;
// 	printf("c[%d]: %s\n", i, c[i]);
// 	return (c);	
// }

void	print_map(t_game *game)
{
	int	i;
	
	i = 0;
	printf("--------\n");
	while(game->map[i])
	{
		printf("%s", game->map[i++]);
	}
	printf("\n--------\n");
}

// int main(void)
// {
// 	printf("check main:-1\n");

//     char **area;
//     t_point size = {8, 7};
//     t_point coord = {1, 1};
//     char *zone[] = {
//         "11111111",
// 		"10000001",
// 		"10C00101",
//         "1PCC1E01",
//         "10E10CC1",
//         "1C10CP01",
//         "11111111"
//     };
// 	t_counter counter;
// 	counter.c = 0;
// 	counter.e = 0;
// 	printf("check main:00\n");
//     area = make_area(zone, size);
// 	printf("check main:01\n");
// 	print_tab(area);
// 	printf("check main:02 --- floodfill\n");
// 	printf("Start point: area[%d, %d]: %c\n", coord.x, coord.y, area[coord.x][coord.y]);
//     flood_fill(area, size, coord, &counter);
//     printf("\n");
// 	printf("check main:03\n");
//     print_tab(area);
	
// 	int i;
// 	i = size.y;
// 	while (--i >= 0)
// 		free(area[i]);
// 	free(area);

// 	printf("counter c: %d --- e: %d\n", counter.c, counter.e);
// 	printf("--- END ---\n");
//     return (0);
// }
