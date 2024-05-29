#include "../includes/cub3d.h"

void	init_player(t_file *game_data, t_cub3d *cub3d)
{
	char	direction;

	direction = set_player_position(game_data, cub3d);
	if (direction == 'N')
		cub3d->P->angle = 1.5 * M_PI;
	else if (direction == 'S')
		cub3d->P->angle = 0.5 * M_PI;
	else if (direction == 'E')
		cub3d->P->angle = 0;
	else if (direction == 'W')
		cub3d->P->angle = M_PI;
	cub3d->P->dir = angle_to_vec(cub3d->P->angle);
	cub3d->P->fov = FOV;
}

void	init_minimap(t_file *game_data, t_cub3d *cub3d)
{
	cub3d->minimap->w_tiles = game_data->map_w_tiles;
	cub3d->minimap->h_tiles = game_data->map_h_tiles;
	cub3d->minimap->w_pixels = game_data->map_w_tiles * TILE_SIZE;
	cub3d->minimap->h_pixels = game_data->map_h_tiles * TILE_SIZE;
	copy_map(game_data, cub3d->minimap);
	// print minimap --> remove this before submitting
	for (size_t i = 0; i < cub3d->minimap->h_tiles; i++)
	{
		for (size_t j = 0; j < cub3d->minimap->w_tiles; j++)
			printf("%d", cub3d->minimap->map[i][j]);
		printf("\n");
	}
}

void	init_textures(t_file *game_data, t_cub3d *cub3d)
{
	cub3d->textures[NORTH] = game_data->textures[NORTH];
	cub3d->textures[SOUTH] = game_data->textures[SOUTH];
	cub3d->textures[EAST] = game_data->textures[EAST];
	cub3d->textures[WEST] = game_data->textures[WEST];
	cub3d->floor = get_rgba(game_data->floor[0], game_data->floor[1], game_data->floor[2], 255);
	cub3d->ceiling = get_rgba(game_data->ceiling[0], game_data->ceiling[1], game_data->ceiling[2], 255);
}

// init cub3d struct
void	init(t_cub3d *cub3d, t_file *game_data)
{
	cub3d->width = 920;
	cub3d->height = 800;
	cub3d->P = malloc(sizeof(t_player));
	if (!cub3d->P)
		return ; // add proper error message
	init_player(game_data, cub3d);
	init_textures(game_data, cub3d);
	cub3d->minimap = malloc(sizeof(t_minimap));
	if (!cub3d->minimap)
		return ; // add proper error message
	init_minimap(game_data, cub3d);
}
