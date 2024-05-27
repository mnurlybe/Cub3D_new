/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:31:48 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/27 19:39:22 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	set_player_position(t_file *game_data, t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < game_data->map_h_tiles)
	{
		while (j < game_data->map_w_tiles)
		{
			if (game_data->map[i][j] == 'N' || game_data->map[i][j] == 'S'
				|| game_data->map[i][j] == 'E' || game_data->map[i][j] == 'W')
			{
				cub3d->P->pos.x = (j + 0.5) * TILE_SIZE;
				cub3d->P->pos.y = (i + 0.5) * TILE_SIZE;
				return (game_data->map[i][j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	update_direction(t_cub3d *cub3d, double direction)
{
	cub3d->P->angle += direction;
	if (cub3d->P->angle < 0)
		cub3d->P->angle += 2 * M_PI;
	else if (cub3d->P->angle > 2 * M_PI)
		cub3d->P->angle -= 2 * M_PI;
	cub3d->P->dir = angle_to_vec(cub3d->P->angle);
}
