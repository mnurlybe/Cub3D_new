#include "../includes/cub3d.h"

void init(t_cub3d *cub3d)
{
    cub3d->width = 1024;
    cub3d->height = 1024;
    cub3d->P = malloc(sizeof(t_player));
    cub3d->P->mini_x = MINIMAP_SIZE / 2;
    cub3d->P->mini_y = MINIMAP_SIZE / 2;
    cub3d->P->dir = M_PI_2;
    cub3d->P->fov = FOV;
    cub3d->minimap = malloc(sizeof(t_minimap));
    cub3d->minimap->width = MINIMAP_SIZE;
    cub3d->minimap->height = MINIMAP_SIZE;
    cub3d->minimap->map = malloc(sizeof(int *) * 8);
    for (size_t i = 0; i < 8; i++)
        cub3d->minimap->map[i] = malloc(sizeof(int) * 8);
    // set the borders to 1
    for (size_t i = 0; i < 8; i++)
    {
        cub3d->minimap->map[0][i] = 1;
        cub3d->minimap->map[7][i] = 1;
        cub3d->minimap->map[i][0] = 1;
        cub3d->minimap->map[i][7] = 1;
    }
    // provide in the comments the map as an array of 1 and 0
    // 1 is a wall, 0 is a free space
    // 1 1 1 1 1 1 1 1
    // 1 0 0 1 0 0 0 1
    // 1 0 0 1 0 0 0 1
    // 1 0 0 0 0 0 0 1
    // 1 0 0 0 0 0 0 1
    // 1 0 1 0 0 1 0 1
    // 1 1 0 0 0 0 0 1
    // 1 1 1 1 1 1 1 1
    cub3d->minimap->map[1][3] = 1;
    cub3d->minimap->map[2][3] = 1;
    cub3d->minimap->map[5][2] = 1;
    cub3d->minimap->map[5][5] = 1;
    cub3d->minimap->map[6][1] = 1;
}
