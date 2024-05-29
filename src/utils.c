/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:21 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/29 20:47:30 by lwoiton          ###   ########.fr       */
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
