/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:59 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/03 18:10:04 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

// define constants
// Screen settings
# define SCREEN_WIDTH 920
# define SCREEN_HEIGHT 800

// Player settings
# define FOV 60
# define PLAYER_SPEED 0.1
# define PLAYER_ROT_SPEED 0.02

// Map settings
# define PLAYER_SIZE 6
# define MINIMAP_SCALE 16
# define TILE_SIZE 1

// Sprite settings
# define SPRITE_SPEED 0.5
# define SPRITE_PATH "./textures/sprite_s.png"

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
 * @fov: A double representing the player's field of view.
 * 			This is typically in degrees.
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

typedef struct s_sprite
{
	t_vec_int		pos;
	mlx_texture_t	*tex;
	double			direction;
	double			counter;
}					t_sprite;

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
	mlx_texture_t	*textures[4];
	t_sprite		*sprite;
}					t_file;

// mlx struct window, image and their dimenstions
typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*buf;
	size_t			width;
	size_t			height;
	t_player		*p;
	mlx_texture_t	*textures[4];
	t_sprite		*sprite;
	uint32_t		floor;
	uint32_t		ceiling;
	t_minimap		*minimap;
}					t_cub3d;

typedef struct s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_color;

// draw_minimap.c
// void draw_map(void *ptr);
// void draw_player(t_cub3d *cub3d);

// draw_minimap_vis.c
void				draw_map_vis(void *ptr);

// cast field of view
void				cast_fov(void *ptr);

// init.c
void				init(t_cub3d *cub3d, t_file *game_data);

// keys.c
void				handle_keys(void *ptr);
void				handle_mouse(void *ptr);

/**
 * Rotates the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 */
void				rotation(t_cub3d *cub3d);

/**
 * This function updates the
 * player's position on the map based on the current direction of the player.
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
int					check_floor_ceiling(char **floor, char **ceiling);
int					check_textures(t_file *info);

// check_file_utils.c
int					is_only_whitespace(char *line);
int					is_only_ones(char *line);
int					array_len(char **array);
int					is_num(char *str);
int					is_only_allowed_chars(char *str);

// check_file_utils_2.c
int					parse_textures(t_file *info);
int					parse_rgb(char *floor, char *ceiling, t_file *info);
int					parse_floor_ceiling(t_file *info);
int					validate_borders(char *line, size_t end_index,
						size_t start_index);

// map_utils.cimg
int					get_map(t_file *game);
void				copy_map(t_file *game_data, t_minimap *minimap);

// map_utils2.c
int					get_map_indexes(t_file *info);

// player_utils.c
char				set_player_position(t_file *game_data, t_cub3d *cub3d);
/**
 * Updates the direction of the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 * @param direction The new direction to update the player's direction to.
 */
void				update_direction(t_cub3d *cub3d, double direction);

// raycasting_utils.c
bool				vertical_gridline_hit(t_vec *d);
int					is_tile_wall(t_cub3d *cub3d, t_ray *ray, t_vec_int map,
						int wall_type);
t_vec_int			stepping_direction(t_vec dir);

// raycasting.c
void				cast_ray(t_cub3d *cub3d, t_ray *ray);
void				dda(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist, 
						t_vec *distance);
t_vec				calculate_initial_offset(t_cub3d *cub3d, t_ray *ray,
						t_vec delta_dist);

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
int					get_rgba(int r, int g, int b, int a);
uint32_t			get_pixel_color(mlx_texture_t *texture, int x, int y);
int					is_newline(char c);
void				draw_line_vis(mlx_image_t *img, t_vec p1, t_vec p2,
						int color);

void				render_sprite(t_cub3d *cub3d);
#endif
