#include "../includes/cub3d.h"

char set_player_position(t_file *game_data, t_cub3d *cub3d)
{
    size_t i = 0;
    size_t j = 0;
    while (i < game_data->map_h_tiles)
    {
        while (j < game_data->map_w_tiles)
        {
            if (game_data->map[i][j] == 'N' || game_data->map[i][j] == 'S' || game_data->map[i][j] == 'E' || game_data->map[i][j] == 'W')
            {
                cub3d->P->mini_x = (j + 0.5) * MINIMAP_TILE_SIZE;
                cub3d->P->mini_y = (i + 0.5) * MINIMAP_TILE_SIZE;
                return (game_data->map[i][j]);
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (0);
}