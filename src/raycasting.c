/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:52:40 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/10 18:32:22 by lwoiton          ###   ########.fr       */
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
// 3. The player direction should be a float value (Maybe not needed anymore)
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

int nearest_int(double value)
{
	if (value >= 0)
		return ((int) (value + 0.5));
	else
		return ((int) (value - 0.5));
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
        mlx_put_pixel(img, nearest_int(x), nearest_int(y), color); // Use rounding to nearest integer
        x += xinc;
        y += yinc;
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

void	raycast(t_cub3d *cub3d, t_ray *ray)
{
	t_vec p = cub3d->P->pos;
	int map_x = p.x / TILE_SIZE;
	int map_y = p.y / TILE_SIZE;
	//t_vec map = vec_scal_m(cub3d->P->pos, (double) 1 / TILE_SIZE);
	t_vec dir = ray->dir;
	double delta_dist_x = (fabs(dir.x) < 1e-10) ? 0.0 : sqrt(1 + (dir.y * dir.y) / (dir.x * dir.x));
	double delta_dist_y = (fabs(dir.y) < 1e-10) ? 0.0 : sqrt(1 + (dir.x * dir.x) / (dir.y * dir.y));
	t_vec side_dist;
	if (dir.x < 0)
		side_dist.x = (p.x - map_x * TILE_SIZE) * delta_dist_x;
	else
		side_dist.x = ((map_x + 1) * TILE_SIZE - p.x) * delta_dist_x;
	if (dir.y < 0)
		side_dist.y = (p.y - map_y * TILE_SIZE) * delta_dist_y;
	else
		side_dist.y = ((map_y + 1) * TILE_SIZE - p.y) * delta_dist_y;
	int x;
	int y;
	int step_x = (dir.x < 0) ? -1 : 1;
	int step_y = (dir.y < 0) ? -1 : 1;
	while (true)
	{
		if ((side_dist.x < side_dist.y && side_dist.x > 1e-10)|| side_dist.y < 1e-10)
		{
			if (dir.x < 0)
				x = map_x * TILE_SIZE;
			else
				x = (map_x + 1) * TILE_SIZE;
			y = nearest_x_or_y(p.y + (x - p.x) * tan(ray->angle), cub3d->minimap->h_pixels);
			//draw_rotated_cross(cub3d->img, x, y, 4, 2, ORANGE);
		}
		else
		{
			if (dir.y < 0)
				y = map_y * TILE_SIZE;
			else
				y = (map_y + 1) * TILE_SIZE;
			x = nearest_x_or_y(p.x + (y - p.y) / tan(ray->angle), cub3d->minimap->w_pixels);
			//draw_circle_trig(cub3d->img, x, y, 5, 1,TURQUOISE);
		}
		if ((side_dist.x < side_dist.y && side_dist.x > 1e-10) || side_dist.y < 1e-10)
		{
			map_x += step_x;
			ray->wall = cub3d->minimap->map[map_y][map_x];
			if (ray->wall > 0)
			{
				if (dir.x < 0)
					ray->side = 'W';
				else
					ray->side = 'E';
				break;
			}
			side_dist.x += delta_dist_x * TILE_SIZE;
		}
		else
		{
			map_y += step_y;
			ray->wall = cub3d->minimap->map[map_y][map_x];
			if (ray->wall > 0)
			{
				if (dir.y < 0)
					ray->side = 'N';
				else
					ray->side = 'S';
				break;
			}
			side_dist.y += delta_dist_y * TILE_SIZE;
		}
	}
	//draw_line2(cub3d->img, p.x, p.y, x, y, 0x00FF0000);
	ray->pos.x = x;
	ray->pos.y = y;
	ray->distance = ((side_dist.x < side_dist.y && side_dist.x > 1e-10) || side_dist.y < 1e-10) ? side_dist.x : side_dist.y;
	ray->distance *= cos(cub3d->P->dir - ray->angle);
}

/* void draw_view(t_cub3d *cub3d, t_ray *ray)
{
	int min_x = ray->index * (cub3d->width / FOV);
	int max_x = (ray->index + 1) * (cub3d->width / FOV);
	int curr_color;
	if (ray->side == 'N')
		curr_color = GREEN;
	else if (ray->side == 'S')
		curr_color = BLUE;
	else if (ray->side == 'E')
		curr_color = RED;
	else if (ray->side == 'W')
		curr_color = YELLOW;
	int current_height = (int) (cub3d->height / ray->distance);
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
} */

void draw_view(t_cub3d *cub3d, t_ray *ray)
{
    int min_x = ray->index * (cub3d->width / FOV);
    int max_x = (ray->index + 1) * (cub3d->width / FOV);
    int texture_width = TEXTURE_WIDTH; // Assume TEXTURE_WIDTH is defined
    int texture_height = TEXTURE_HEIGHT; // Assume TEXTURE_HEIGHT is defined
    uint32_t **texture;

    switch(ray->side) {
        case 'N': texture = cub3d->textures.north; break;
        case 'S': texture = cub3d->textures.south; break;
        case 'E': texture = cub3d->textures.east; break;
        case 'W': texture = cub3d->textures.west; break;
    }

    int current_height = (int) (cub3d->height / ray->distance);
    int start = (cub3d->height - current_height) / 2;
    int end = start + current_height;

    for (int x = min_x; x < max_x; x++)
    {
        for (int y = start; y < end; y++)
        {
            double texPos = (y - start) / (double)current_height;
            int texY = texPos * texture_height;
            double wallX; // Where exactly the wall was hit

            if(ray->side == 'N' || ray->side == 'S') {
                wallX = cub3d->P->pos.x + ray->distance * ray->dir.x;
            } else {
                wallX = cub3d->P->pos.y + ray->distance * ray->dir.y;
            }
            wallX -= floor(wallX); // Get fractional part

            int texX = (int)(wallX * (double)texture_width);
            if(ray->side == 'E' || ray->side == 'S') texX = texture_width - texX - 1; // Reverse texture on these walls

            uint32_t color = texture[texY][texX];
            mlx_put_pixel(cub3d->img, x, y, color);
        }
        for (int y = 0; y < start; y++) // Ceiling
            mlx_put_pixel(cub3d->img, x, y, 0x00FFFFFF);
        for (int y = end; y < cub3d->height; y++) // Floor
            mlx_put_pixel(cub3d->img, x, y, 0xFF000000);
    }
}


void	fov_cast(void *ptr)
{
	t_cub3d	*cub3d = (t_cub3d *) ptr;
	t_ray	ray;

	ray.index = 0;
	double curr_dir = deg_to_rad(-FOV / 2);
	while (curr_dir < deg_to_rad(FOV / 2))
	{
		ray.index++;
		ray.angle = cub3d->P->dir + curr_dir;
		ray.dir = angle_to_vec(cub3d->P->dir + curr_dir);
		raycast(cub3d, &ray);
		draw_view(cub3d, &ray);
		curr_dir += deg_to_rad(1);
	}
}
