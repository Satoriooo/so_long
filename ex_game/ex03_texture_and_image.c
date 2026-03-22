#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*wall_img;
}	t_data;

int	main(void)
{
	t_data	data;
	int		w, h;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Image test");

	data.wall_img = mlx_xpm_file_to_image(data.mlx_ptr, "wall.xpm", &w, &h);

	if (!data.wall_img)
	{
		printf("Error: Could not load image!\n");
		return (1);
	}

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.wall_img, 50, 50);

	mlx_loop(data.mlx_ptr);
	return (0);
}