/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:21 by lwoiton           #+#    #+#             */
/*   Updated: 2024/06/03 16:50:18 by lwoiton          ###   ########.fr       */
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

int	is_newline(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

// draw a thicker line starting in the middle of the player square
void	draw_line_vis(mlx_image_t *img, t_vec p1, t_vec p2, int color)
{
	t_vec	inc;
	size_t	i;
	size_t	j;
	size_t	k;

	inc = vec_scal_d(vec_sub(p2, p1), vec_distance(p2, p1));
	i = 0;
	while (i < vec_distance(p2, p1))
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				mlx_put_pixel(img, p1.x + j, p1.y + k, color);
				k++;
			}
			j++;
		}
		p1 = vec_add(p1, inc);
		i++;
	}
}
