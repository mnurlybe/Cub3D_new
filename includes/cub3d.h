/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:08:59 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/10 19:38:32 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

// define constants
# define FOV 60
# define PLAYER_SPEED 0.05
# define PLAYER_ROT_SPEED 0.005
# define PLAYER_SIZE 6
# define MINIMAP_SCALE 1.0
# define TILE_SIZE 8
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

// Color codes
# define RED		0xFF0000FF
# define GREEN		0x008000FF
# define BLUE		0x0000FFFF
# define WHITE		0xFFFFFFFF
# define BLACK		0x000000FF
# define YELLOW		0xFFFF00FF
# define CYAN		0x00FFFFFF
# define MAGENTA	0xFF00FFFF
# define ORANGE		0xFFA500FF
# define TURQUOISE	0x40E0D0FF


# define PLAYER_COLOR MAGENTA

/**
 * @struct t_vec
 * @brief Represents a 2D vector with x and y coordinates.
 *
 * This structure is used to store 2D coordinates in the form of a vector.
 * The x and y members represent the x and y coordinates respectively.
 */
typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	int		index;
	t_vec	pos;
	double	angle;
	t_vec	dir;
	int		wall;
	int 	side;
	double 	distance;
}	t_ray;

typedef struct s_tex
{
	mlx_image_t	*img;
	int			width;
	int			height;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
}	t_tex;

/**
 * Struct s_player - Represents a player in the 2D world.
 * @pos: A t_vec struct representing the player's position in the world.
 * @dir: A double representing the direction the player is facing in radians.
 * @fov: A double representing the player's field of view. This is typically in degrees.
 */
typedef struct s_player
{
    t_vec	pos;
	t_vec	dir_vec;
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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	char	**map;
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
	t_tex 		textures[4];
	t_minimap	*minimap;
}				t_cub3d;

// draw_minimap.c
void draw_map(void *ptr);
void draw_player(t_cub3d *cub3d);

//cast field of view
void	fov_cast(void *ptr);
int		nearest_int(double x);

// init.c
void init(t_cub3d *cub3d, t_file *game_data);

// parse_file.c
t_file *parse_file(char *file);

// map_utils.c
void get_map(t_file *game);
void    copy_map(t_file *game_data, t_minimap *minimap);

// keys.c
void handle_keys(void *ptr);

// movement.c
/**
 * Updates the direction of the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 * @param direction The new direction to update the player's direction to.
 */
void update_direction(t_cub3d *cub3d, double direction);

/**
 * Rotates the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 */
void rotation(t_cub3d *cub3d);

/**
 * @brief Updates the position of the player on the map depending on the current direction (angle in radians).
 * 
 * @details This function updates the player's position on the map based on the current direction of the player.
 * 
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 * @param angle The angle to update the player's position by.
 */
void update_position(t_cub3d *cub3d, double angle);

/**
 * Moves the player in the game.
 *
 * @param cub3d The pointer to the t_cub3d struct representing the game state.
 */
void move_player(t_cub3d *cub3d);

/**
 * Handles the movement of the player in the game.
 *
 * @param ptr A pointer to the game state.
 */
void handle_movement(void *ptr);

// free.c
void free_program(t_cub3d *cub3d);
void free_game(t_file *game);

// parse_file.c
t_file *parse_file(char *file);

// map_utils.c
void get_map(t_file *game);
void    copy_map(t_file *game_data, t_minimap *minimap);

// player_utils.c
char set_player_position(t_file *game_data, t_cub3d *cub3d);

// utils.c

/**
 * Checks if a given position is not colliding with a wall.
 *
 * @param map The map of the game.
 * @param pos The position to check.
 * @return 1 if the position is not colliding with a wall, 0 otherwise.
 */
int is_wall(int **map, t_vec pos);


/**
 * Converts an angle to a vector representation. The vector is normalized to pixel.
 *
 * @param angle The angle in radians.
 * @return The noramlized direction vector.
 */
t_vec angle_to_vec(double angle);

// vector_utils.c
/**
 * Adds two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
t_vec	vec_add(t_vec a, t_vec b);

/**
 * Subtracts two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The difference between the two vectors.
 */
t_vec	vec_sub(t_vec a, t_vec b);

/**
 * Scales a vector by a scalar value (multiplication).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec	vec_scal_m(t_vec a, double scalar);

/**
 * Scales a vector by a scalar value (division).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec	vec_scal_d(t_vec a, double scalar);

/**
 * Calculates the dot product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
double	vec_dot(t_vec a, t_vec b);

/**
 * Calculates the length (magnitude) of a vector.
 *
 * @param a The vector.
 * @return The length of the vector.
 */
double	vec_len(t_vec a);

/**
 * Normalizes a vector (makes it a unit vector).
 *
 * @param a The vector to be normalized.
 * @return The normalized vector.
 */
t_vec	vec_normalize(t_vec a);

/**
 * Rotates a vector by a given angle (in radians).
 *
 * @param a The vector to be rotated.
 * @param angle The angle of rotation (in radians).
 * @return The rotated vector.
 */
t_vec	vec_rotate(t_vec a, double angle);

#endif