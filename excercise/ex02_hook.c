#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

int handle_keypress(int keysym, void *param)
{
	printf("Key pressed: %d\n", keysym);

	if (keysym == 65307)
	{
		printf("Closing window... \n");
		exit(0);
	}
	return (0);
}

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "Interact with me!");

	mlx_key_hook(win_ptr, handle_keypress, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}