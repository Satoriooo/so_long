#include <fcntl.h>
#include <stdio.h>
#include "ex_map.h"

#define BUFFER_SIZE 42

int	count_nl(int fd)
{
	char *line;
	int n;

	line = get_next_line(fd);
	while(line != NULL)
	{
		line = get_next_line(fd);
		n++;
	}
	return (n);
}