/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:39 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/04/28 16:26:16 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int    ft_cub3d(void)
{
    t_cub3d    *cub3d;
    cub3d = malloc(sizeof(t_cub3d));
    init(cub3d);
    cub3d->mlx = mlx_init(cub3d->width, cub3d->height, "Cub3D", true);
    if (!cub3d->mlx)
    {
        free(cub3d);
        return (1);
    }
    cub3d->img = mlx_new_image(cub3d->mlx, cub3d->width, cub3d->height);
    if (!cub3d->img)
    {
        free(cub3d);
        return (1); 
    }
    mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);  

    mlx_put_pixel(cub3d->img, 250, 250, 0xFF0000FF);
    
    mlx_loop_hook(cub3d->mlx, draw_minimap, cub3d);
    mlx_loop_hook(cub3d->mlx, handle_movement, cub3d);
    mlx_loop_hook(cub3d->mlx, handle_keys, cub3d);
    mlx_loop(cub3d->mlx);
    mlx_delete_image(cub3d->mlx, cub3d->img);
	mlx_close_window(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
	free_program(cub3d);
    return (0);
}


int main(int argc, char **argv)
{
    (void) argv;
    (void) argc;
    // if (argc == 2)
    ft_cub3d();
    // else
    //     write(1, "Error\n", 6);
    return (0);
}