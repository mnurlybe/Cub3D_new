/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:35:24 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/29 20:03:41 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	vertical_gridline_hit(t_vec *d)
{
	return ((d->x < d->y && !is_zero(d->x)) || is_zero(d->y));
}

int	is_tile_wall(t_cub3d *cub3d, t_ray *ray, t_vec_int map, int wall_type)
{
	ray->wall = cub3d->minimap->map[map.y][map.x];
	if (ray->wall == 0)
		return (ray->wall);
	if (wall_type == 1)
	{
		if (ray->dir.x > 0)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
	else if (wall_type == 0)
	{
		if (ray->dir.y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	return (ray->wall);
}

t_vec_int	stepping_direction(t_vec dir)
{
	t_vec_int	step;

	if (dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}
