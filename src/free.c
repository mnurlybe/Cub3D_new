/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:31 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 17:36:58 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_program(t_cub3d *cub3d)
{
	size_t	i;

	free(cub3d->P);
	i = 0;
	while (i < cub3d->minimap->h_tiles)
	{
		free(cub3d->minimap->map[i]);
		i++;
	}
	free(cub3d->minimap->map);
	free(cub3d->minimap);
	if (cub3d->sprite->tex)
		mlx_delete_texture(cub3d->sprite->tex);
	free(cub3d->sprite);
	free(cub3d);
}

void	free_textures(t_file *game)
{
	if (game->no != NULL)
		free_array(game->no);
	if (game->so != NULL)
		free_array(game->so);
	if (game->we != NULL)
		free_array(game->we);
	if (game->ea != NULL)
		free_array(game->ea);
	if (game->textures[NORTH])
	{
		printf("free north\n");
		mlx_delete_texture(game->textures[NORTH]);
	}
	if (game->textures[SOUTH] != NULL)
	{
		printf("free south\n");
		mlx_delete_texture(game->textures[SOUTH]);
	}
	if (game->textures[EAST] != NULL)
	{
		printf("free east\n");
		mlx_delete_texture(game->textures[EAST]);
	}
	if (game->textures[WEST] != NULL)
	{
		printf("free west\n");
		mlx_delete_texture(game->textures[WEST]);
	}
}

void	free_game(t_file *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->split_file != NULL)
		free_array(game->split_file);
	if (game->map != NULL)
		free_array(game->map);
	free(game);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
