// gnl reads a map file
// take the returned lines and make it into 2D char array

/*
// TODO: Check if the map is valid
	- If its rectangular -> OK
	- If its surrounded by walls -> OK
	- If there's a valid path -> On going...
	(- You need to able to parse any kind of map, as long as it respects the rules above)
	- If the map contains player, exit, and all the collectibles (at least one) (check starts from the starting position)
	- Show the number of current movements
	- 
*/

// #include <fcntl.h>
// #include <stdio.h>
// #include "get_next_line.h"

// char	**read_map(void)
// {
// 	int		fd = open("sample1.txt", O_RDONLY);
// 	int		cnt;
// 	int 	i;

// 	char	*line;
// 	char 	**map;

// 	cnt = 0;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		cnt++;
// 		free(line);
// 	}
// 	if (cnt = 0)
// 		return NULL; // if gnl is empty, then ... 
// 	map = malloc(sizeof(char *) * cnt + 1);
	
// 	i = 0;
// 	while (i < cnt)
// 	{}

// 	return (0);
// }

