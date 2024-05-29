/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:50:37 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 17:46:28 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	loop_program(t_cub3d *cub3d)
{
	mlx_image_t	*tmp;

	mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
	mlx_loop_hook(cub3d->mlx, handle_movement, cub3d);
	mlx_loop_hook(cub3d->mlx, handle_keys, cub3d);
    mlx_loop_hook(cub3d->mlx, handle_mouse, cub3d);
	mlx_loop_hook(cub3d->mlx, cast_fov, cub3d);
	mlx_loop_hook(cub3d->mlx, draw_map_vis, cub3d);
	tmp = cub3d->img;
	cub3d->img = cub3d->buf;
	cub3d->buf = tmp;
	mlx_loop(cub3d->mlx);
}

void	close_program(t_cub3d *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->buf);
	mlx_delete_image(cub3d->mlx, cub3d->img);
	//mlx_close_window(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
	free_program(cub3d);
}

int	ft_cub3d(t_file *game_data)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	init(cub3d, game_data);
	cub3d->mlx = mlx_init(cub3d->width, cub3d->height, "Cub3D", true);
	if (!cub3d->mlx)
	{
		free(cub3d);
		return (1);
	}
	cub3d->img = mlx_new_image(cub3d->mlx, cub3d->width, cub3d->height);
	cub3d->buf = mlx_new_image(cub3d->mlx, cub3d->width, cub3d->height);
	if (!cub3d->img || !cub3d->buf)
	{
		free(cub3d);
		return (1);
	}
	loop_program(cub3d);
	close_program(cub3d);
	return (0);
}

int	main(int argc, char **argv)
{
	t_file	*game;

	(void)argv; // add proper error message
	(void)argc;
	game = NULL;
	if (argc == 2)
	{
		game = parse_file(argv[1]);
		if (!game)
			write(2, "Error in file\n", 15); // add proper error message
		else
		{
			ft_cub3d(game);
		}
	}
	else                        // add proper error message
		write(2, "Error\n", 6); // add proper error message
	free_game(game);
	return (0);
}
