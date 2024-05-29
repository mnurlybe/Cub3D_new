/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:38:54 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 20:40:29 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
In this file the handling of the player movement will be done,
	by implementing KEY_PRESS and KEY_RELEASE events.
The player will be able to move forward, backward, rotate left and right.
The direction_line should be drawn to show the direction/rotation of the player.
The handle_movement function will be called in the mlx_loop_hook function.
*/

void	rotation(t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		update_direction(cub3d, -PLAYER_ROT_SPEED);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		update_direction(cub3d, PLAYER_ROT_SPEED);
}

t_vec	wallslide(t_cub3d *cub3d, double angle)
{
	t_vec	new_dir1;
	t_vec	new_dir2;
	t_vec	new_pos1;
	t_vec	new_pos2;

	new_dir1 = (t_vec){.x = 0, .y = cub3d->p->dir.y};
	new_dir2 = (t_vec){.x = cub3d->p->dir.x, .y = 0};
	new_pos1 = vec_add(cub3d->p->pos, vec_scal_m(vec_rotate(new_dir1, angle),
				PLAYER_SPEED));
	new_pos2 = vec_add(cub3d->p->pos, vec_scal_m(vec_rotate(new_dir2, angle),
				PLAYER_SPEED));
	if (!is_wall(cub3d->minimap->map, new_pos1))
		return (new_pos1);
	else if (!is_wall(cub3d->minimap->map, new_pos2))
		return (new_pos2);
	else
		return (cub3d->p->pos);
}

void	update_position(t_cub3d *cub3d, double angle)
{
	t_vec	new_pos;

	new_pos = vec_add(cub3d->p->pos, vec_scal_m(vec_rotate(cub3d->p->dir,
					angle), PLAYER_SPEED));
	if (!is_wall(cub3d->minimap->map, new_pos))
		cub3d->p->pos = new_pos;
	else
		cub3d->p->pos = wallslide(cub3d, angle);
}

void	move_player(t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		update_position(cub3d, 0);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		update_position(cub3d, -M_PI);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		update_position(cub3d, M_PI_2);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		update_position(cub3d, -M_PI_2);
}

void	handle_movement(void *ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)ptr;
	rotation(cub3d);
	move_player(cub3d);
}
