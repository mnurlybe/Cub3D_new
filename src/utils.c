#include "../includes/cub3d.h"

int is_wall(int **map, t_vec new_pos)
{
    return (map[(int) (new_pos.y/ TILE_SIZE)][(int) (new_pos.x/ TILE_SIZE)]);
}

t_vec angle_to_vec(double angle)
{
	t_vec result;

	result.x = cos(angle);
	result.y = sin(angle);
	return (result);
}

void load_textures(t_cub3d *cub3d, t_file *game_data)
{
	cub3d->NO = mlx_xpm_file_to_image(cub3d->mlx, game_data->no, &cub3d->NO->width, &cub3d->NO->height);
	cub3d->SO = mlx_xpm_file_to_image(cub3d->mlx, game_data->so, &cub3d->SO->width, &cub3d->SO->height);
	cub3d->WE = mlx_xpm_file_to_image(cub3d->mlx, game_data->we, &cub3d->WE->width, &cub3d->WE->height);
	cub3d->EA = mlx_xpm_file_to_image(cub3d->mlx, game_data->ea, &cub3d->EA->width, &cub3d->EA->height);
}