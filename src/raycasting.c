/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:01:41 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 17:49:59 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>

t_vec	calculate_initial_offset(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist,
		t_vec_int map)
{
	t_vec	p;
	t_vec	offset;

	p = cub3d->P->pos;
	if (ray->dir.x < 0)
		offset.x = (p.x - map.x * TILE_SIZE) * delta_dist.x;
	else
		offset.x = ((map.x + 1) * TILE_SIZE - p.x) * delta_dist.x;
	if (ray->dir.y < 0)
		offset.y = (p.y - map.y * TILE_SIZE) * delta_dist.y;
	else
		offset.y = ((map.y + 1) * TILE_SIZE - p.y) * delta_dist.y;
	return (offset);
}

void	dda(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist, t_vec_int map,
		t_vec *distance)
{
	t_vec_int	step;

	step = stepping_direction(ray->dir);
	while (true)
	{
		if (vertical_gridline_hit(distance))
		{
			map.x += step.x;
			if (is_tile_wall(cub3d, ray, map, 1))
				break ;
			distance->x += delta_dist.x * TILE_SIZE;
		}
		else
		{
			map.y += step.y;
			if (is_tile_wall(cub3d, ray, map, 0))
				break ;
			distance->y += delta_dist.y * TILE_SIZE;
		}
	}
}

void	cast_ray(t_cub3d *cub3d, t_ray *ray)
{
	t_vec		delta_dist;
	t_vec		distance;
	t_vec_int	map;

	delta_dist = vec_apply(vec_inv(ray->dir), fabs);
	map = vec_int_scal_d(cub3d->P->pos, TILE_SIZE);
	distance = calculate_initial_offset(cub3d, ray, delta_dist, map);
	dda(cub3d, ray, delta_dist, map, &distance);
	if (vertical_gridline_hit(&distance))
		ray->distance = distance.x;
	else
		ray->distance = distance.y;
	ray->wall_hit = vec_add(cub3d->P->pos, vec_scal_m(ray->dir, ray->distance));
	ray->distance *= cos(cub3d->P->angle - ray->angle);
}

void	cast_fov(void *ptr)
{
	t_cub3d	*cub3d;
	t_ray	ray;
	double	fov_rad;
	double	ray_inc;

	cub3d = (t_cub3d *)ptr;
	fov_rad = deg_to_rad(cub3d->P->fov);
	ray_inc = fov_rad / cub3d->width;
	cub3d = (t_cub3d *)ptr;
	ray.index = 0;
	while (ray.index < (int)cub3d->width)
	{
		ray.angle = cub3d->P->angle - fov_rad / 2 + ray.index * ray_inc;
		ray.dir = angle_to_vec(ray.angle);
		cast_ray(cub3d, &ray);
		render_vertical_stripe(cub3d, &ray);
		//render_sprite(cub3d, &ray);
		ray.index++;
	}
}
