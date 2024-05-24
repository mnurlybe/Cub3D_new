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
    return ("");
}

void    init_textures(t_file *game_data, t_cub3d *cub3d)
{
    int index = 0;
    while (game_data->texture_paths[index])
    {
        cub3d->textures[index] = mlx_load_png(game_data->texture_paths[index]);
        if (!cub3d->textures[index])
        {
            printf("Error loading texture %s\n", game_data->texture_paths[index]);
            exit(1);
        }
        else
            printf("%s %s\n", get_wall_side(index), game_data->texture_paths[index]);
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
