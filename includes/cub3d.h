/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:52:16 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/01 09:58:58 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

// define constants
# define FOV 60
# define PLAYER_SPEED 5
# define PLAYER_ROT_SPEED 0.157
# define PLAYER_SIZE 10
# define MINIMAP_SCALE 1.0
# define MINIMAP_SIZE 512
# define TILE_SIZE 64
// to calculate the cos and sin will be used the M_PI constant
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

// create an array of 1 and 0 to represent the map

// player struct: that will have a player position, direction and field of view
typedef struct s_player
{
	double	mini_x;
	double	mini_y;
	double	dir;
	double	fov;
}				t_player;

// minimap struct
typedef struct s_minimap
{
	size_t	width;
	size_t	height;
	int 	**map;
}				t_minimap;

// mlx struct window, image and their dimenstions
typedef struct s_cub3d
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	size_t		width;
	size_t		height;
	t_player	*P;
	t_minimap	*minimap;
}				t_cub3d;


// draw_minimap.c
void draw_minimap(void *ptr);

//cast field of view
void fov_cast(void *ptr);

// init.c
void init(t_cub3d *cub3d);

// movement.c
void handle_movement(void *ptr);

// keys.c
void handle_keys(void *ptr);

#endif
