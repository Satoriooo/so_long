#include <stdio.h>

int ft_strlen(char *s)
{
	int n;
	
	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	check_left(char **map, int cnt)
{
	int i;

	i = 0;
	while(i < cnt)
	{
		if (map[i][0] != '1')
		{
			printf("check_left map[%d][0]: %c\n", i, map[i][0]);
			return (0);
		}
		printf("check_left map line: %s\n", map[i]);
		i++;
	}
	if (i < 3)
		return (0);
	return (1);
}

int	check_top(char **map, int cnt)
{
	int i;

	i = 0;
	while(map[0][i])
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	if (i < 3)
		return (0);
	return (1);
}

int	check_right(char **map, int cnt)
{
	int i;
	int	pre_len;
	int cur_len;

	pre_len = 0;
	i = 0;
	while(i < cnt)
	{
		cur_len = ft_strlen(map[i]);
		if (pre_len != 0 && pre_len != cur_len)
			return (0);
		if (map[i][cur_len - 1] != '1')
			return (0);
		pre_len = cur_len;
		i++;
	}
	return (1);
}

int	check_bottom(char **map, int cnt)
{
	int	i;

	i = 0;
	cnt--;
	while(map[cnt][i])
	{
		if (map[cnt][i] != '1')
			return (0);
		printf("map[%d][%d] : %c\n", cnt, i, map[cnt][i]);
		i++;
	}
	return (1);
}

int is_shape_valid(char **map, int cnt)
{
	int	n;

	n = 0;
	n += check_left(map, cnt);
	n += check_top(map,cnt);
	n += check_right(map,cnt);
	n += check_bottom(map, cnt);

	if (n == 4)
		return (1);
	printf("invalid map\n");
	return (0);
}

int main()
{
	char 	*map[] = {
        "1111111",
        "1000C01",
        "1011101",
        "101E101",
        "1000C01",
		"1111111"
    };

	int cnt = sizeof(map)/sizeof(map[0]);

	if (is_shape_valid(map, cnt) == 1)
		printf("The shape is valid\n");
	else
		printf("The shape is NOT valid\n");

	if (is_element_valid(map, cnt) == 1)
		// It checks...
			// - if theres only (0, 1, P, E, C)
			// - if there's only one (P, E) on the entire map
			// - if there are all of C in floodfill area
			// - '0' can remain left out side of floodfill area

		printf("The shape is valid\n");
	else
		printf("The shape is NOT valid\n");

}