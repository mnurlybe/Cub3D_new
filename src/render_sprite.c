/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:51:44 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/29 14:58:20 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprite_position(t_sprite *s)
{
	if (s->counter > 50)
		s->direction = -SPRITE_SPEED;
	else if (s->counter < 0)
		s->direction = SPRITE_SPEED;
	s->counter += s->direction;
}

void	render_sprite(t_cub3d *cub3d)
{
	t_sprite		*s;
	unsigned int	j;
	unsigned int	k;
	uint32_t		color;

	s = cub3d->sprite;
	j = 0;
	while (j < s->tex->height)
	{
		k = 0;
		while (k < s->tex->width)
		{
			color = get_pixel_color(s->tex, k, j);
			if (color)
				mlx_put_pixel(cub3d->buf, s->pos.x + k, s->pos.y + j
					+ s->counter, color);
			k++;
		}
		j++;
	}
	update_sprite_position(s);
}
