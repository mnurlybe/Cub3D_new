# include "cub3d.h"

void	render_sprite(t_cub3d *cub3d)
{

	int x;
	int	y;
	int j;
	int	k;

	x = cub3d->sprite->sprite->width;
	y = cub3d->sprite->sprite->height;
	j = 0;
	k = 0;
	while (j < y)
	{
		while (k < x)
		{
			uint32_t color = get_pixel_color(cub3d->sprite->sprite, k, j);
			if (color != 0x000000)
				mlx_put_pixel(cub3d->buf, cub3d->sprite->pos.x + k, cub3d->sprite->pos.y + j + cub3d->sprite->counter, color);
			k++;
		}
		k = 0;
		j++;
	}
	if (cub3d->sprite->counter > 50)
		cub3d->sprite->direction = -0.5;
	else if (cub3d->sprite->counter < 0)
		cub3d->sprite->direction = 0.5;
	cub3d->sprite->counter += cub3d->sprite->direction;

}


