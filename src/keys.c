/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:03 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 19:25:06 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// handle esc key to close the window
void	handle_keys(void *ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)ptr;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub3d->mlx);
	}
}

void	handle_mouse(void *ptr)
{
	t_cub3d		*cub3d;
	int			delta;
	t_vec_int	m;

	cub3d = (t_cub3d *)ptr;
	if (!mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		return ;
	mlx_get_mouse_pos(cub3d->mlx, &m.x, &m.y);
	delta = m.x - (int)cub3d->width / 2;
	if (delta > 2)
	{
		update_direction(cub3d, PLAYER_ROT_SPEED * delta / 5);
		mlx_set_mouse_pos(cub3d->mlx, cub3d->width / 2, cub3d->height / 2);
	}
	else if (delta < - 2)
	{
		update_direction(cub3d, PLAYER_ROT_SPEED * delta / 5);
		mlx_set_mouse_pos(cub3d->mlx, cub3d->width / 2, cub3d->height / 2);
	}
}
