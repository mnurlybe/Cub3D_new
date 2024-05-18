/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:59 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/18 18:54:07 by julienmoign      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

// define constants
# define FOV 60
# define PLAYER_SPEED 5
# define PLAYER_ROT_SPEED 0.157
# define PLAYER_SIZE 6
# define MINIMAP_SCALE 1.0
# define TILE_SIZE 32
# define TILE_SIZE 32
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

// player struct: that will have a player position, direction and field of view
typedef struct s_player
{
	double	mini_x; // in pixels
	double	mini_y; // in pixels
	double	dir;
	double	fov;
}				t_player;

// minimap struct
typedef struct s_minimap
{
	int 	**map;
	size_t	w_tiles;
	size_t	h_tiles;
	size_t  w_pixels;
	size_t  h_pixels;
}				t_minimap;

// file struct
typedef struct s_file
{
	int 	fd;
	size_t 	file_size;
	char 	**split_file;
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
	int		map_start_index;
	int 	map_end_index;
	size_t  map_h_tiles;
	size_t  map_w_tiles;
}				t_file;

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
void draw_map(void *ptr);
void draw_player(t_cub3d *cub3d);

//cast field of view
void fov_cast(void *ptr);

// init.c
void init(t_cub3d *cub3d, t_file *game_data);

// keys.c
void handle_keys(void *ptr);
void handle_movement(void *ptr);

// free.c
void free_program(t_cub3d *cub3d);
void free_game(t_file *game);
void free_array(char **arr);
void free_textures(t_file *game);

// parse_file.c
t_file *parse_file(char *file);

// check_file.c
int check_file(t_file *info);

// check_file_utils.c
int is_only_whitespace(char *line);
int is_only_ones(char *line);
int array_len(char **array);
int is_num(char *str);
int is_only_allowed_chars(char *str);

// map_utils.c
int get_map(t_file *game);
void    copy_map(t_file *game_data, t_minimap *minimap);

// player_utils.c
char set_player_position(t_file *game_data, t_cub3d *cub3d);


// print_testing.c
void print_textures(t_file *info);
void print_floor_ceiling(char **arr);

#endif