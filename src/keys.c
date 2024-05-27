/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:03 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/27 16:40:51 by mnurlybe         ###   ########.fr       */
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
		mlx_terminate(cub3d->mlx);
		free(cub3d);
		exit(0);
	}
}
