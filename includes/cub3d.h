/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:59 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/28 16:53:19 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

// define constants
# define FOV 60
# define PLAYER_SPEED 0.09
# define PLAYER_ROT_SPEED 0.015
# define PLAYER_SIZE 6
# define MINIMAP_SCALE 1.0
# define TILE_SIZE 8
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

// Color codes
# define RED 0xFF0000FF
# define GREEN 0x008000FF
# define BLUE 0x0000FFFF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define YELLOW 0xFFFF00FF
# define CYAN 0x00FFFFFF
# define MAGENTA 0xFF00FFFF
# define ORANGE 0xFFA500FF
# define TURQUOISE 0x40E0D0FF

# define PLAYER_COLOR MAGENTA

typedef enum e_wallside
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
}					t_wallside;

typedef struct s_tex_map
{
	mlx_texture_t	*tex;
	double			wall_x;
	t_vec_int		cord;
	uint32_t		color;
}					t_tex_map;

typedef struct s_vertical
{
	int				delta_height;
	int				start;
	int				end;
}					t_vertical;

typedef struct s_ray
{
	int				index;
	t_vec			wall_hit;
	t_vec			dir;
	double			angle;
	int				wall;
	t_wallside		side;
	double			distance;
}					t_ray;

/**
 * Struct s_player - Represents a player in the 2D world.
 * @pos: A t_vec struct representing the player's position in the world.
 * @dir: A double representing the direction the player is facing in radians.

	* @fov: A double representing the player's field of view. This is typically in degrees.
 */
typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	double			angle;
	double			fov;
}					t_player;

// minimap struct
typedef struct s_minimap
{
	int				**map;
	size_t			w_tiles;
	size_t			h_tiles;
	size_t			w_pixels;
	size_t			h_pixels;
}					t_minimap;

// file struct
typedef struct s_file
{
	int				fd;
	size_t			file_size;
	char			**split_file;
	char			**no;
	char			**so;
	char			**we;
	char			**ea;
	int				floor[3];
	int				ceiling[3];
	char			**map;
	int				map_start_index;
	int				map_end_index;
	size_t			map_h_tiles;
	size_t			map_w_tiles;
}					t_file;

typedef struct s_sprite
{
	mlx_texture_t	*tex[5];
	t_vec			pos;
	int				counter;
	int				current;
	double			distance;
}					t_sprite;

// mlx struct window, image and their dimenstions
typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*buf;
	size_t			width;
	size_t			height;
	t_player		*P;
	mlx_texture_t	*textures[6];
	uint32_t		floor;
	uint32_t		ceiling;
	t_minimap		*minimap;
}					t_cub3d;

// draw_minimap.c
void				draw_map(void *ptr);
void				draw_player(t_cub3d *cub3d);

// cast field of view
void				cast_fov(void *ptr);

// init.c
void				init(t_cub3d *cub3d, t_file *game_data);

// keys.c
void				handle_keys(void *ptr);

// movement.c
/**
 * Updates the direction of the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 * @param direction The new direction to update the player's direction to.
 */
void				update_direction(t_cub3d *cub3d, double direction);

/**
 * Rotates the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 */
void				rotation(t_cub3d *cub3d);

/**

	* @brief Updates the position of the player on the map depending on the current direction (angle in radians).
 *

	* @details This function updates the player's position on the map based on the current direction of the player.
 *
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 * @param angle The angle to update the player's position by.
 */
void				update_position(t_cub3d *cub3d, double angle);

/**
 * Moves the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 */
void				move_player(t_cub3d *cub3d);

/**
 * Handles the movement of the player in the game.
 *
 * @param ptr A pointer to the game state.
 */
void				handle_movement(void *ptr);

// free.c
void				free_program(t_cub3d *cub3d);
void				free_game(t_file *game);
void				free_array(char **arr);
void				free_textures(t_file *game);

// parse_file.cimg
t_file				*parse_file(char *file);

// check_file.c
int					check_file(t_file *info);

// check_file_utils.c
int					is_only_whitespace(char *line);
int					is_only_ones(char *line);
int					array_len(char **array);
int					is_num(char *str);
int					is_only_allowed_chars(char *str);

// map_utils.cimg
int					get_map(t_file *game);
void				copy_map(t_file *game_data, t_minimap *minimap);

// player_utils.c
char				set_player_position(t_file *game_data, t_cub3d *cub3d);

// raycasting_utils.c
bool				vertical_gridline_hit(t_vec *d);
int					is_tile_wall(t_cub3d *cub3d, t_ray *ray, t_vec_int map,
						int wall_type);
t_vec_int			stepping_direction(t_vec dir);

// raycasting.c
void				cast_ray(t_cub3d *cub3d, t_ray *ray);
void				dda(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist,
						t_vec_int map, t_vec *distance);
t_vec				calculate_initial_offset(t_cub3d *cub3d, t_ray *ray,
						t_vec delta_dist, t_vec_int map);

// render_vertical.c
t_vertical			calculate_vertical_strip(t_cub3d *cub3d, t_ray *ray);
void				determ_x_coord_on_texture(t_ray *ray, t_tex_map *tm);
void				determ_y_coord_on_texture(int y, int start,
						int delta_height, t_tex_map *tm);
void				render_vertical_stripe(t_cub3d *cub3d, t_ray *ray);

// utils.c
int					is_wall(int **map, t_vec new_pos);
double				deg_to_rad(double angle);
int					is_zero(double value);
uint32_t			get_pixel_color(mlx_texture_t *texture, int x, int y);

/**
 * Checks if a given position is not colliding with a wall.
 *
 * @param map The map of the game.
 * @param pos The position to check.
 * @return 1 if the position is not colliding with a wall, 0 otherwise.
 */
int					is_wall(int **map, t_vec pos);

#endif
