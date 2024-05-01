/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:52:40 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/01 17:00:01 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdbool.h>

//how to cast a ray properly into a specific direction?
// What kind of consts do I need? What structures do I need?

//Applying the DDA (Digital Differential Analysis) Algorithm
//to determing if the ray hit a border

void draw_line2(mlx_image_t *img, double x1, double y1, double x2, double y2, int color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = sqrt(dx * dx + dy * dy);
    double xinc = dx / steps;
    double yinc = dy / steps;
    double x = x1;
    double y = y1;
    for (size_t i = 0; i < steps; i++)
    {
        for (size_t j = 0; j < 1; j++)
        {
            for (size_t k = 0; k < 1; k++)
            {
                mlx_put_pixel(img, x + j, y + k, color);
            }
        }
        x += xinc;
        y += yinc;
    }
}

void	raycast(t_cub3d *cub3d, double dir)
{
	float	dir_x = cos(dir);
	float	dir_y = sin(dir);
	int		map_x = cub3d->P->mini_x / TILE_SIZE;
	int		map_y = cub3d->P->mini_y / TILE_SIZE;
	int		step_x = dir_x < 0 ? -1 : 1;
	int		step_y = dir_y < 0 ? -1 : 1;

	float	side_dist_x;
	float	side_dist_y;
	float	distance = 0;
	
	float	delta_dist_x;
	float	delta_dist_y;
	delta_dist_x = fabs(1 / dir_x) * TILE_SIZE;
	delta_dist_y = fabs(1 / dir_y) * TILE_SIZE;
	//printf("delta: ( %f| %f)\n\n", delta_dist_x, delta_dist_y);
	if (dir_x < 0)
		side_dist_x = ((map_x + 1) * TILE_SIZE - cub3d->P->mini_x) / fabs( 1 / dir_x); //fabs(dir_x);
	else
		side_dist_x = (cub3d->P->mini_x - map_x * TILE_SIZE) / fabs( 1 / dir_x); //fabs(dir_x);
	if (dir_y < 0)
		side_dist_y = ((map_y + 1) * TILE_SIZE - cub3d->P->mini_y) / fabs( 1 / dir_y); //fabs(dir_y);
	else
		side_dist_y = (cub3d->P->mini_y - map_y * TILE_SIZE) / fabs( 1 / dir_y);//fabs(dir_y);
	//printf("------------------------------------------------------------------------\n");
	//printf("Track iterations:\n");
	//int i = 0;
	//printf(" I |   SD_X   |   SD_Y   |   ->D   |  MAP_X |  MAP_Y |  TILE \n");
    while (true)
	{
		if (side_dist_x < side_dist_y)
		{
            side_dist_x += delta_dist_x;
            map_x += step_x;
            if (cub3d->minimap->map[map_y][map_x] > 0)
			{
                distance = side_dist_x;
                break;
            }
        }
		else
		{
            side_dist_y += delta_dist_y;
            map_y += step_y;
            if (cub3d->minimap->map[map_y][map_x] > 0)
			{
                distance = side_dist_y;
                break;
            }
        }
		//printf("%2d | %6f | %6f | %6f | %5d | %5d | %6d\n", i++, side_dist_x, side_dist_y, distance, map_x, map_y, cub3d->minimap->map[map_y][map_x]);
    }
	//printf("------------------------------------------------------------------------\n");
	double end_x = cub3d->P->mini_x + (double) (distance * dir_x);
	double end_y = cub3d->P->mini_y + (double) (distance * dir_y);
	end_x = fmax(0, fmin(end_x, cub3d->minimap->width));
	end_y = fmax(0, fmin(end_y, cub3d->minimap->height));
	//printf("1: (%lf | %lf) and 2: (%lf | %lf)\n\n\n", cub3d->P->mini_x, cub3d->P->mini_y, end_x, end_y);
	draw_line2(cub3d->img, cub3d->P->mini_x, cub3d->P->mini_y, end_x, end_y, 0x00FF0000);
}

void	fov_cast(void *ptr)
{
	t_cub3d *cub3d = (t_cub3d *) ptr;
	
	raycast(cub3d, cub3d->P->dir);
	/*
	double i = - M_PI_2 / 3;
	while (i < M_PI_2 / 3)
	{
		raycast(cub3d, cub3d->P->dir + i);
		i += M_PI_2 / 32;
	}
	*/
}
