/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:29:10 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/29 14:55:25 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*pixels;
	t_color	col;
	int		i;

	pixels = (uint8_t *)texture->pixels;
	i = (y * texture->width + x) * texture->bytes_per_pixel;
	col.r = pixels[i];
	col.g = pixels[i + 1];
	col.b = pixels[i + 2];
	col.a = pixels[i + 3];
	return ((col.r << 24) | (col.g << 16) | (col.b << 8) | col.a);
}