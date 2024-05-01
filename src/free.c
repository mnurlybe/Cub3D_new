/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:31 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/01 16:26:17 by julienmoign      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_program(t_cub3d *cub3d)
{
    free(cub3d->P);
    for (size_t i = 0; i < 8; i++)
        free(cub3d->minimap->map[i]);
    free(cub3d->minimap->map);
    free(cub3d->minimap);
    free(cub3d);
}

void free_game(t_file *game)
{
    for (size_t i = 0; i < game->file_size; i++)
        free(game->split_file[i]);
    free(game->split_file);
    for (size_t i = 0; game->map[i]; i++)
        free(game->map[i]);
    free(game->map);
    free(game);
}