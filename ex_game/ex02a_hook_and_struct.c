#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

// Our "Master Struct" to hold everything
typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
} t_data;

// Function to close the window and exit cleanly
int close_window(t_data *data)
{
    printf("Cleaning up and exiting...\n");
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    // On Linux, mlx_init memory usually doesn't need a specific free, 
    // but some versions vary. This is the basic cleanup.
    exit(0);
    return (0);
}

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == 65307) // ESC
        close_window(data);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "The Clean Exit");

    // Notice we pass '&data' as the last argument
    mlx_key_hook(data.win_ptr, handle_keypress, &data);

    // This handles clicking the "X" button
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);

    mlx_loop(data.mlx_ptr);
    return (0);
}