/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:50:37 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/11/19 23:59:42 by lwoiton          ###   ########.fr       */
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
	mlx_terminate(cub3d->mlx);
	free_program(cub3d);
}

int	ft_cub3d(t_file *game_data)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	init(cub3d, game_data);
	cub3d->mlx = mlx_init(cub3d->width, cub3d->height, "cub3D", false);
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

	(void)argv;
	(void)argc;
	game = NULL;
	if (argc == 2)
	{
		game = parse_file(argv[1]);
		if (game)
			ft_cub3d(game);
	}
	else
	{
		ft_putstr_fd("Error: wrong arguments.\n", 2);
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 1);
		ft_putstr_fd("Example: ./cub3D maps/simple_map1.cub\n", 1);
	}
	free_game(game);
	return (0);
}
