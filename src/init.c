#include "../includes/cub3d.h"

void init_player(t_file *game_data, t_cub3d *cub3d)
{
    char direction;

    direction = set_player_position(game_data, cub3d);
    if (direction == 'N')
        cub3d->P->angle = 1.5 * M_PI;
    else if (direction == 'S')
        cub3d->P->angle = 0.5 * M_PI;
    else if (direction == 'E')
        cub3d->P->angle = 0;
    else if (direction == 'W')
        cub3d->P->angle = M_PI;
    cub3d->P->angle = 0.5 * M_PI;
    cub3d->P->dir = angle_to_vec(cub3d->P->angle);
    cub3d->P->fov = FOV;
}

void init_minimap(t_file *game_data, t_cub3d *cub3d)
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

char    *get_wall_side(int side)
{
    if (side == NORTH)
        return ("NO");
    else if (side == SOUTH)
        return ("SO");
    else if (side == EAST)
        return ("EA");
    else if (side == WEST)
        return ("WE");
    else if (side == FLOOR)
      return ("F");
    else if (side == CEILING)
      return ("C");
    return ("");
}

void    init_textures(t_file *game_data, t_cub3d *cub3d)
{
    int index = 0;
    cub3d->textures[NORTH] = mlx_load_png(game_data->no[1]);
    cub3d->textures[SOUTH] = mlx_load_png(game_data->so[1]);
    cub3d->textures[EAST] = mlx_load_png(game_data->ea[1]);
    cub3d->textures[WEST] = mlx_load_png(game_data->we[1]);
    cub3d->floor = game_data->floor[0] << 16 | game_data->floor[1] << 8 | game_data->floor[2];
    cub3d->ceiling = game_data->ceiling[0] << 16 | game_data->ceiling[1] << 8 | game_data->ceiling[2];
    while (index < 4)
    {
        if (!cub3d->textures[index])
        {
            write(1, "Error textures\n", 6); // add proper error message
        }
        index++;
    }
}

// init cub3d struct
void init(t_cub3d *cub3d, t_file *game_data)
{
    cub3d->width = 1920;
    cub3d->height = 1080;
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
