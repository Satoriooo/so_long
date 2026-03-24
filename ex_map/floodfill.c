#include <stdio.h>
#include <stdlib.h>

typedef struct s_point {
	int	x;
	int y;
}	t_point;

void flood_fill(char **tab, t_point size, t_point begin)
{
	t_point p;
	static int cnt = 0;
	cnt++;
	printf("flood_fill call: %d\n", cnt);
	p = begin;

	// check if the current position is valid
	if (p.x < 0 || p.x > size.x - 1 || p.y < 0 || p.y > size.y - 1)
		return ;
	if (tab[p.y][p.x] == 'F' || tab[p.y][p.x] == '1')
		return ;
	
	tab[begin.y][begin.x] = 'F';
	p.x--;
	flood_fill(tab, size, p); // Left
	p.x++;
	p.y--;
	flood_fill(tab, size, p); //Up
	p.y++;
	p.x++;
	flood_fill(tab, size, p); // Right
	p.x--;
	p.y++;
	flood_fill(tab, size, p); // Down
}

char **make_area(char **zone, t_point size)
{
	int		i;
	int		j;
	char	**c;

	printf("size.y: %d\n", size.y);
	c = (char **)malloc(sizeof(char *) * (size.y + 1));
	i = 0;
	while(i < size.y)
	{
		printf("make_area i: %d\n", i);
		c[i] = (char *)malloc(sizeof(char) * (size.x + 1));
		j = 0;
		while (j < size.x)
		{
			c[i][j] = zone[i][j];
			j++;
		}
		c[i][j] = '\0';
		i++;
	}
	c[i] = NULL;
	printf("c[%d]: %s\n", i, c[i]);
	return (c);	
}

void	print_tab(char **tab)
{
	int	i;
	
	i = 0;
	printf("--------\n");
	while(tab[i])
	{
		printf("%s\n", tab[i++]);
	}
	printf("--------\n");
}

int main(void)
{
	printf("check main:-1\n");

    char **area;
    t_point size = { 8, 5 };
    t_point begin = { 7, 3 };
    char *zone[] = {
        "11111111",
        "10001001",
        "10010001",
        "10110001",
        "11100001"
    };
	printf("check main:00\n");
    area = make_area(zone, size);
	printf("check main:01\n");
	print_tab(area);
	printf("check main:02\n");
    flood_fill(area, size, begin);
    printf("\n");
	printf("check main:03\n");
    print_tab(area);
	
	int i;
	i = size.y;
	while (--i >= 0)
		free(area[i]);
	free(area);

	printf("--- END ---\n");
    return (0);
}
