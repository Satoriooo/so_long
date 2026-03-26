#include "get_next_line.h"
#include "ex_map.h"

char	*ft_strdup2(char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	printf("strd check00 s: %s\n", s);

	len = 0;
	while (s[len])
		len++;
	printf("strd check01 len: %d\n", (int)len);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	printf("strd check02 dest: %s\n", dest);
	return (dest);
}

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
		map[i] = ft_strdup2(line);
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