#include "ex_map.h"

int main (void)
{
	char *line;
	int fd = open("map1.ber");
	int n = read(fd, buf, 42);

	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}