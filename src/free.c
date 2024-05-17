/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:31 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/12 23:24:20 by lwoiton          ###   ########.fr       */
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

void free_game(t_file *game)
{
    int i;
    i = 0;
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