#include "../includes/cub3d.h"

void init_player(t_file *game_data, t_cub3d *cub3d)
{
    char direction;
    direction = set_player_position(game_data, cub3d);
    if (direction == 'N')
        cub3d->P->dir = 1.5 * M_PI;
    else if (direction == 'S')
        cub3d->P->dir = 0.5 * M_PI;
    else if (direction == 'E')
        cub3d->P->dir = 0;
    else if (direction == 'W')
        cub3d->P->dir = M_PI;
    
    cub3d->P->dir = M_PI;
    cub3d->P->fov = FOV;
}

void init_minimap(t_file *game_data, t_cub3d *cub3d)
{
    cub3d->minimap->w_tiles = game_data->map_w_tiles;
    cub3d->minimap->h_tiles = game_data->map_h_tiles;
    cub3d->minimap->w_pixels = game_data->map_w_tiles * MINIMAP_TILE_SIZE;
    cub3d->minimap->h_pixels = game_data->map_h_tiles * MINIMAP_TILE_SIZE;
    copy_map(game_data, cub3d->minimap);
    // print minimap --> remove this before submitting
    for (size_t i = 0; i < cub3d->minimap->h_tiles; i++)
    {
        for (size_t j = 0; j < cub3d->minimap->w_tiles; j++)
            printf("%d", cub3d->minimap->map[i][j]);
        printf("\n");
    }
}

// init cub3d struct
void init(t_cub3d *cub3d, t_file *game_data)
{
    cub3d->width = 1024;
    cub3d->height = 1024;
    cub3d->P = malloc(sizeof(t_player));
    if (!cub3d->P)
        return ; // add proper error message
    init_player(game_data, cub3d);
    cub3d->minimap = malloc(sizeof(t_minimap));
    if (!cub3d->minimap)
        return ; // add proper error message
    init_minimap(game_data, cub3d);
}
