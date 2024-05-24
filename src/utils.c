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
