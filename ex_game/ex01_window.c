#include "mlx.h"
#include <stdlib.h>

int main (void)
{
	void *mlx_ptr;
	void *win_ptr;

	// Initialize the connection ... Turning on the console
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (1);
	
	// Create the window (and set the size and title)
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "My first mini game");
	if (win_ptr == NULL)
	{
		free(mlx_ptr);
		return (1);
	}

	// Keep the window open
	mlx_loop(mlx_ptr);
	return (0);
}
