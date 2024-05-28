/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:21 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 20:01:50 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(int **map, t_vec new_pos)
{
	return (map[(int)(new_pos.y / TILE_SIZE)][(int)(new_pos.x / TILE_SIZE)]);
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

int	is_zero(double value)
{
	return (fabs(value) < 1e-10);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// Get the red channel.
int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}

uint32_t get_pixel_color(mlx_texture_t *texture, int x, int y)
{
    uint8_t *pixels = (uint8_t *)texture->pixels;
    int index = (y * texture->width + x) * texture->bytes_per_pixel;
    
    uint8_t r = pixels[index];
    uint8_t g = pixels[index + 1];
    uint8_t b = pixels[index + 2];
    uint8_t a = pixels[index + 3];
    
    // Convert ARGB to RGBA if needed
    uint32_t rgba = (r << 24) | (g << 16) | (b << 8) | a;

    return rgba;
}