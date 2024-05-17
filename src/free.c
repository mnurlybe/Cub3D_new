/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:31 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/17 21:37:57 by julienmoign      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_program(t_cub3d *cub3d)
{
    size_t i;
    free(cub3d->P);
    i = 0;
    while (i < cub3d->minimap->h_tiles)
    {
        free(cub3d->minimap->map[i]);
        i++;
    }
    free(cub3d->minimap->map);
    free(cub3d->minimap);
    free(cub3d);
}

void free_textures(t_file *game)
{
    int i;
    i = 0;
    while (i < 2)
    {
        free(game->no[i]);
        free(game->so[i]);
        free(game->we[i]);
        free(game->ea[i]);
        i++;
    }
    free(game->no);
    free(game->so);
    free(game->we);
    free(game->ea);
}


void free_game(t_file *game)
{
    int i;
    i = 0;
    free_textures(game);
    while(game->split_file[i])
    {
        free(game->split_file[i]);
        i++;
    }
    free(game->split_file);
    i = 0;
    while(game->map[i])
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
    free(game);
}

void free_array(char **arr)
{
    int i;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}