/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:53:24 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 20:40:29 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_file *game_data, t_cub3d *cub3d)
{
	char	direction;

	direction = set_player_position(game_data, cub3d);
	if (direction == 'N')
		cub3d->p->angle = 1.5 * M_PI;
	else if (direction == 'S')
		cub3d->p->angle = 0.5 * M_PI;
	else if (direction == 'E')
		cub3d->p->angle = 0;
	else if (direction == 'W')
		cub3d->p->angle = M_PI;
	cub3d->p->dir = angle_to_vec(cub3d->p->angle);
	cub3d->p->fov = FOV;
}

void	init_minimap(t_file *game_data, t_cub3d *cub3d)
{
	cub3d->minimap->w_tiles = game_data->map_w_tiles;
	cub3d->minimap->h_tiles = game_data->map_h_tiles;
	cub3d->minimap->w_pixels = game_data->map_w_tiles * MINIMAP_SCALE;
	cub3d->minimap->h_pixels = game_data->map_h_tiles * MINIMAP_SCALE;
	copy_map(game_data, cub3d->minimap);
}

void	init_textures(t_file *game_data, t_cub3d *cub3d)
{
	cub3d->textures[NORTH] = game_data->textures[NORTH];
	cub3d->textures[SOUTH] = game_data->textures[SOUTH];
	cub3d->textures[EAST] = game_data->textures[EAST];
	cub3d->textures[WEST] = game_data->textures[WEST];
	cub3d->floor = get_rgba(game_data->floor[0], game_data->floor[1],
			game_data->floor[2], 255);
	cub3d->ceiling = get_rgba(game_data->ceiling[0], game_data->ceiling[1],
			game_data->ceiling[2], 255);
}

t_sprite	*init_sprite(t_cub3d *cub3d)
{
	cub3d->sprite = malloc(sizeof(t_sprite));
	if (!cub3d->sprite)
	{
		ft_putstr_fd("Error during memory allocation: sprite.\n", 2);
		return (NULL);
	}
	cub3d->sprite->tex = mlx_load_png(SPRITE_PATH);
	cub3d->sprite->pos = (t_vec_int){.x = cub3d->width
		- cub3d->sprite->tex->width - 10, .y = 10};
	cub3d->sprite->counter = 0;
	cub3d->sprite->direction = SPRITE_SPEED;
	return (cub3d->sprite);
}

// init cub3d struct
void	init(t_cub3d *cub3d, t_file *game_data)
{
	cub3d->width = SCREEN_WIDTH;
	cub3d->height = SCREEN_HEIGHT;
	cub3d->p = malloc(sizeof(t_player));
	if (!cub3d->p)
	{
		ft_putstr_fd("Error during memory allocation: Player.\n", 2);
		return ;
	}
	init_player(game_data, cub3d);
	init_textures(game_data, cub3d);
	if (!init_sprite(cub3d))
		return ;
	cub3d->minimap = malloc(sizeof(t_minimap));
	if (!cub3d->minimap)
	{
		ft_putstr_fd("Error during memory allocation: minimap.\n", 2);
		return ;
	}
	init_minimap(game_data, cub3d);
}
