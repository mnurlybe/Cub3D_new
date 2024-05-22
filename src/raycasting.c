/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:52:40 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/16 13:54:56 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

// TODO Clean up the coordinates
//@
// TODO: Deleted unnecessary lines and comments
// TODO: Improve 3D rendering
//			- Implement rendering of sprites
//			- Implement rendering of the floor and ceiling
//			- Implement rendering of the skybox
//			- Implement rendering of the HUD
//			- Implement rendering of the minimap

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
					ray->side = WEST;
				else
					ray->side = EAST;
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
					ray->side = NORTH;
				else
					ray->side = SOUTH;
				break;
			}
			side_dist.y += delta_dist_y * TILE_SIZE;
		}
	}
	//draw_line2(cub3d->img, p.x, p.y, x, y, 0x00FF0000);
	ray->wall_hit.x = x;
	ray->wall_hit.y = y;
	ray->distance = ((side_dist.x < side_dist.y && side_dist.x > 1e-10) || side_dist.y < 1e-10) ? side_dist.x : side_dist.y;
	ray->distance *= cos(cub3d->P->dir - ray->angle);
}

uint32_t get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	uint32_t *pixels = (uint32_t *)texture->pixels;
	return (pixels[y * texture->width + x]);
}

uint32_t interpolate_colors(uint32_t c1, uint32_t c2, double alpha) {
    uint8_t r = (uint8_t)((1 - alpha) * ((c1 >> 16) & 0xFF) + alpha * ((c2 >> 16) & 0xFF));
    uint8_t g = (uint8_t)((1 - alpha) * ((c1 >> 8) & 0xFF) + alpha * ((c2 >> 8) & 0xFF));
    uint8_t b = (uint8_t)((1 - alpha) * (c1 & 0xFF) + alpha * (c2 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

uint32_t texture_sample_bilinear(mlx_texture_t *tex, double u, double v) {
    // Convert fractional texture coordinates to texel indices
    double tx = u * tex->width - 0.5;
    double ty = v * tex->height - 0.5;

    // Determine texel indices surrounding the point
    int x1 = (int)floor(tx);
    int y1 = (int)floor(ty);
    int x2 = (x1 + 1) % tex->width;
    int y2 = (y1 + 1) % tex->height;

    // Calculate fractional parts of u and v
    double fx = tx - floor(tx);
    double fy = ty - floor(ty);

    // Fetch four texels
    uint32_t c11 = tex->pixels[y1 * tex->width + x1];
    uint32_t c21 = tex->pixels[y1 * tex->width + x2];
    uint32_t c12 = tex->pixels[y2 * tex->width + x1];
    uint32_t c22 = tex->pixels[y2 * tex->width + x2];

    // Interpolate between the colors
    uint32_t interp1 = interpolate_colors(c11, c21, fx);
    uint32_t interp2 = interpolate_colors(c12, c22, fx);
    uint32_t finalColor = interpolate_colors(interp1, interp2, fy);

    return finalColor;
}

void draw_view(t_cub3d *cub3d, t_ray *ray)
{
	int min_x = ray->index * (cub3d->width / FOV);
	int max_x = (ray->index + 1) * (cub3d->width / FOV);
	int delta_height = (int) (cub3d->height / ray->distance);
	int start = (cub3d->height - delta_height) / 2;
	int end = start + delta_height;

	int tex_num = ray->side;
	// Calculate exact position on the wall texture
	double wallHitX = cub3d->P->pos.x + ray->distance * cos(ray->angle); // Use cosine to adjust for fisheye effect
	double wallHitY = cub3d->P->pos.y + ray->distance * sin(ray->angle);

	// Correct texture coordinates based on wall side
	double wallX = (ray->side == NORTH || ray->side == SOUTH) ? wallHitX : wallHitY;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)cub3d->textures[tex_num]->width);
	for (int x = min_x; x < max_x; x++)
	{
		for (int y = 0; y < (int) cub3d->height; y++)
		{
			if (y >= start && y <= end)
			{
			    int texY = ((y - start) * cub3d->textures[tex_num]->height) / delta_height;
			    texY = texY % cub3d->textures[tex_num]->height;  // Handle wrapping
			    //uint32_t color = texture_sample_bilinear(cub3d->textures[tex_num], texX, texY);
			    uint32_t color = get_pixel_color(cub3d->textures[tex_num], texX, texY);
			    mlx_put_pixel(cub3d->img, x, y, color);
			}
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
	t_ray	ray;

	ray.index = 0;
	double curr_dir = deg_to_rad(-FOV / 2);
	while (curr_dir < deg_to_rad(FOV / 2))
	{
		ray.angle = cub3d->P->dir + curr_dir;
		ray.dir = angle_to_vec(cub3d->P->dir + curr_dir);
		raycast(cub3d, &ray);
		//check_get_pixel(cub3d->img, cub3d->textures[0]);
		draw_view(cub3d, &ray);
		//draw_textured_wall(cub3d, &ray);
		curr_dir += deg_to_rad(1);
		ray.index++;
	}
}
