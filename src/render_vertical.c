/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vertical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:49 by lwoiton           #+#    #+#             */
/*   Updated: 2024/06/03 18:11:40 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vertical	calculate_vertical_strip(t_cub3d *cub3d, t_ray *ray)
{
	t_vertical	vert;

	vert.delta_height = (int)(cub3d->height / (ray->distance));
	vert.start = (int)(cub3d->height - vert.delta_height) / 2;
	vert.end = (int)(vert.start + vert.delta_height);
	return (vert);
}

void	determ_x_coord_on_texture(t_ray *ray, t_tex_map *tm)
{
	if (ray->side == NORTH || ray->side == SOUTH)
		tm->wall_x = ray->wall_hit.x;
	else
		tm->wall_x = ray->wall_hit.y;
	tm->wall_x -= floor(tm->wall_x);
	tm->cord.x = (int)(tm->wall_x * (double)tm->tex->width);
}

void	determ_y_coord_on_texture(int y, int start, int delta_height,
			t_tex_map *tm)
{
	tm->cord.y = (int)((y - start) * (double)tm->tex->height / delta_height);
	tm->cord.y = tm->cord.y % tm->tex->height;
}

void	render_vertical_stripe(t_cub3d *cub3d, t_ray *ray)
{
	t_vertical	vert;
	t_tex_map	tm;
	int			y;

	vert = calculate_vertical_strip(cub3d, ray);
	tm.tex = cub3d->textures[ray->side];
	determ_x_coord_on_texture(ray, &tm);
	y = 0;
	while (y < (int)cub3d->height)
	{
		if (y >= vert.start && y <= vert.end)
		{
			determ_y_coord_on_texture(y, vert.start, vert.delta_height, &tm);
			tm.color = get_pixel_color(tm.tex, tm.cord.x, tm.cord.y);
			mlx_put_pixel(cub3d->buf, ray->index, y, tm.color);
		}
		else if (y < vert.start)
			mlx_put_pixel(cub3d->buf, ray->index, y, cub3d->ceiling);
		else
			mlx_put_pixel(cub3d->buf, ray->index, y, cub3d->floor);
		y++;
	}
}
