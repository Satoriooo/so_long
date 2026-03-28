#include <stdio.h>
#include <stdlib.h>

typedef struct s_point {
	int	x;
	int y;
}	t_point;

typedef struct s_counter
{
	int c;
	int e;
}	t_counter;

void flood_fill(char **tab, t_point size, t_point begin, t_counter *counter)
{
	t_point p;
	static int cnt = 0;
	cnt++;
	printf("flood_fill call: %d\n", cnt);
	p = begin;

	// check if the current position is valid
	if (p.x < 0 || p.x > size.x - 1 || p.y < 0 || p.y > size.y - 1)
		return ;
	// If its wall or 'F', do nothing and return
	if (tab[p.y][p.x] == 'F' || tab[p.y][p.x] == '1')
		return ;
	// If it's 'C', count++
	// if it's 'E', flag++
	if (tab[p.y][p.x] == 'C')
	{
		counter->c++;
		printf("counter c: %d --- e: %d\n", counter->c, counter->e);
	}
	if (tab[p.y][p.x] == 'E')
		counter->e++;

	tab[p.y][p.x] = 'F';
	if (cnt > 100)
		return ;
		
	p.x--;
	flood_fill(tab, size, p, counter); // Left !!!
	p.x++;
	p.y--;
	flood_fill(tab, size, p, counter); //Up
	p.y++;
	p.x++;
	flood_fill(tab, size, p, counter); // Right
	p.x--;
	p.y++;
	flood_fill(tab, size, p, counter); // Down
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
    t_point size = {8, 7};
    t_point begin = {1, 1};
    char *zone[] = {
        "11111111",
		"10000001",
		"10C00101",
        "1PCC1E01",
        "10E10CC1",
        "1C10CP01",
        "11111111"
    };
	t_counter counter;
	counter.c = 0;
	counter.e = 0;
	printf("check main:00\n");
    area = make_area(zone, size);
	printf("check main:01\n");
	print_tab(area);
	printf("check main:02 --- floodfill\n");
	printf("Start point: area[%d, %d]: %c\n", begin.x, begin.y, area[begin.x][begin.y]);
    flood_fill(area, size, begin, &counter);
    printf("\n");
	printf("check main:03\n");
    print_tab(area);
	
	int i;
	i = size.y;
	while (--i >= 0)
		free(area[i]);
	free(area);

	printf("counter c: %d --- e: %d\n", counter.c, counter.e);
	printf("--- END ---\n");
    return (0);
}
