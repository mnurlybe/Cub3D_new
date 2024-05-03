/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:52:40 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/03 16:38:53 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

//how to cast a ray properly into a specific direction?
// What kind of consts do I need? What structures do I need?

//Applying the DDA (Digital Differential Analysis) Algorithm
//to determing if the ray hit a border

//Changes I would like to introduce:
// 1. I would like to have a struct that holds the player position as vector
// 2. The player position should be a integer value
// 3. The player direction should be a float value
// 4. FOV should be in radient value
// 5. We should also include .d files so that we can recompile the project whent he header files change
// 6. The player movement should not be dependent on the frame rate or the refresh rate of the screen


// TODO: Implement edge case when the ray is vertical or horizontal
// TODO: Improve structure of the code
// TODO: Deleted unnecessary lines and comments
// TODO: Improve 3D rendering
//			- Implement rendring of different textures
//			- Implement rendering of sprites
//			- Implement rendering of the floor and ceiling
//			- Implement rendering of the skybox
//			- Implement rendering of the HUD
//			- Implement rendering of the minimap

// TODO: 


# define deg_to_rad(angle) (angle * M_PI / 180)
# define rad_to_deg(radient) (radient * 180 / M_PI)

#define ORANGE 0xFFFFA500
#define TURQUOISE 0xFF40E0D0

void draw_cross(mlx_image_t *img, int x, int y, int size, int color)
{
	for (int i = -size; i <= size; i++)
	{
		if (x + i >= 0 && x + i < (int)img->width)
		{
			mlx_put_pixel(img, x + i, y, color);
		}
		if (y + i >= 0 && y + i < (int)img->height)
		{
			mlx_put_pixel(img, x, y + i, color);
		}
	}
}

void draw_rotated_cross(mlx_image_t *img, int x, int y, int size, int thickness, int color) {
    for (int i = -size; i <= size; i++) {
        for (int j = -thickness; j <= thickness; j++) {
            // Diagonal 1 (\)
            int xi = x + i + j;
            int yi = y + i + j;
            if (xi >= 0 && (uint32_t)xi < img->width && yi >= 0 && (uint32_t)yi < img->height) {
                mlx_put_pixel(img, xi, yi, color);
            }

            // Diagonal 2 (/)
            xi = x + i - j;
            yi = y - i + j;
            if (xi >= 0 && (uint32_t)xi < img->width && yi >= 0 && (uint32_t)yi < img->height) {
                mlx_put_pixel(img, xi, yi, color);
            }
        }
    }
}

void draw_circle_trig(mlx_image_t *img, int center_x, int center_y, int radius, int thickness, int color) {
    for (int r = radius - thickness; r <= radius + thickness; r++) {
        for (int theta = 0; theta < 360; theta++) {
            int x = center_x + r * cos(theta * M_PI / 180.0);
            int y = center_y + r * sin(theta * M_PI / 180.0);

            if (x >= 0 && (uint32_t)x < img->width && y >= 0 && (uint32_t)y < img->height) {
                mlx_put_pixel(img, x, y, color);
            }
        }
    }
}

void draw_line2(mlx_image_t *img, double x1, double y1, double x2, double y2, int color) {
    int dx = (int)(x2 - x1);
    int dy = (int)(y2 - y1);
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); // Choose maximum of dx or dy for steps

    double xinc = dx / (double)steps;
    double yinc = dy / (double)steps;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= steps; i++) { // Iterate up to and including steps
        mlx_put_pixel(img, (int)(x + 0.5), (int)(y + 0.5), color); // Use rounding to nearest integer
        x += xinc;
        y += yinc;
    }
}

int nearest_int(double value) {
	if (value >= 0) {
		return (int)(value + 0.5);
	} else {
		return (int)(value - 0.5);
	}
}

int nearest_x_or_y(double value, int max_value) {
	if (fabs(value) < 1e-10) {
		return nearest_int(value);
	} else {
		int result = (int)value;
		if (result < 0) {
			result = 0;
		} else if (result >= max_value) {
			result = max_value - 1;
		}
		return result;
	}
}

double	raycast(t_cub3d *cub3d, double dir)
{
	int p_x = cub3d->P->mini_x;
	int p_y = cub3d->P->mini_y;
	int map_x = p_x / TILE_SIZE;
	int map_y = p_y / TILE_SIZE;
	double dir_x = cos(dir);
	double dir_y = sin(dir);
	double delta_dist_x = (fabs(dir_x) < 1e-10) ? 0.0 : sqrt(1 + (dir_y * dir_y) / (dir_x * dir_x));
	double delta_dist_y = (fabs(dir_y) < 1e-10) ? 0.0 : sqrt(1 + (dir_x * dir_x) / (dir_y * dir_y));
	double side_dist_x;
	double side_dist_y;
	if (dir_x < 0)
		side_dist_x = (p_x - map_x * TILE_SIZE) * delta_dist_x;
	else
		side_dist_x = ((map_x + 1) * TILE_SIZE - p_x) * delta_dist_x;
	if (dir_y < 0)
		side_dist_y = (p_y - map_y * TILE_SIZE) * delta_dist_y;
	else
		side_dist_y = ((map_y + 1) * TILE_SIZE - p_y) * delta_dist_y;
	int x;
	int y;
	int step_x = (dir_x < 0) ? -1 : 1;
	int step_y = (dir_y < 0) ? -1 : 1;
	while (true)
	{
		if (side_dist_x < side_dist_y)
		{
			if (dir_x < 0)
				x = map_x * TILE_SIZE;
			else
				x = (map_x + 1) * TILE_SIZE;
			y = nearest_x_or_y(p_y + (x - p_x) * tan(dir), cub3d->minimap->height);
			//draw_rotated_cross(cub3d->img, x, y, 4, 2, ORANGE);
		}
		else
		{
			if (dir_y < 0)
				y = map_y * TILE_SIZE;
			else
				y = (map_y + 1) * TILE_SIZE;
			x = nearest_x_or_y(p_x + (y - p_y) / tan(dir), cub3d->minimap->width);
			//draw_circle_trig(cub3d->img, x, y, 5, 1,TURQUOISE);
		}
		if (side_dist_x < side_dist_y)
		{
			map_x += step_x;
			if (cub3d->minimap->map[map_y][map_x] > 0)
				break;
			side_dist_x += delta_dist_x * TILE_SIZE;
		}
		else
		{
			map_y += step_y;
			if (cub3d->minimap->map[map_y][map_x] > 0)
				break;
			side_dist_y += delta_dist_y * TILE_SIZE;
		}
	}
	//draw_line2(cub3d->img, p_x, p_y, x, y, 0x00FF0000);
	double prep_wall_dist = (side_dist_x < side_dist_y) ? side_dist_x : side_dist_y;
	prep_wall_dist *= cos(cub3d->P->dir - dir);
	
	return (prep_wall_dist);
}

void draw_view(t_cub3d *cub3d, double distance, int i)
{
	int min_x = i * (cub3d->width / FOV);
	int max_x = (i + 1) * (cub3d->width / FOV);
	int curr_color = 0xFF0000FF;
	int current_height = (int)(cub3d->height / distance);
	int start = (cub3d->height - current_height) / 2;
	int end = start + current_height;
	for (int x = min_x; x < max_x; x++)
	{
		for (int y = 0; y < (int) cub3d->height; y++)
		{
			if (y >= start && y <= end)
				mlx_put_pixel(cub3d->img, x, y, curr_color);
			else if (y < start)
				mlx_put_pixel(cub3d->img, x, y, 0x00FFFFFF);
			else
				mlx_put_pixel(cub3d->img, x, y, 0xFF000000);
		}
	}
}

void	fov_cast(void *ptr)
{
	t_cub3d	*cub3d = (t_cub3d *) ptr;
	int		i = 0;
	double	distance;

	double curr_dir = deg_to_rad(-FOV / 2);
	while (curr_dir < deg_to_rad(FOV / 2))
	{
		distance = raycast(cub3d, cub3d->P->dir + curr_dir);
		draw_view(cub3d, distance, i++);
		curr_dir += deg_to_rad(1);
	}
}
