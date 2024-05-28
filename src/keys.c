#include "../includes/cub3d.h"

// handle esc key to close the window
void handle_keys(void *ptr)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)ptr;
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(cub3d->mlx);
        mlx_terminate(cub3d->mlx);
        free(cub3d);
        exit(0);
    }
}

void handle_mouse(void *ptr)
{
	t_cub3d		*cub3d;
	t_vec_int	m;

	cub3d = (t_cub3d *)ptr;
	mlx_get_mouse_pos(cub3d->mlx, &m.x, &m.y);
	if (m.x > (int)cub3d->width / 2 + 5)
	{
		update_direction(cub3d, PLAYER_ROT_SPEED);
		mlx_set_mouse_pos(cub3d->mlx, cub3d->width / 2, cub3d->height / 2);
	}
	else if (m.x < (int)cub3d->width / 2 - 5)
	{
		update_direction(cub3d, - PLAYER_ROT_SPEED);
		mlx_set_mouse_pos(cub3d->mlx, cub3d->width / 2, cub3d->height / 2);
	}
		
}