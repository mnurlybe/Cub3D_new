/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:31 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/04/28 16:26:10 by mnurlybe         ###   ########.fr       */
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