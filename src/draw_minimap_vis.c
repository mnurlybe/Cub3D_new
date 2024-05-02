#include "../includes/cub3d.h"

/**
 * this will be another version of draw_minimap, where only visible part will be drawn centered around player
 * The visible minimap will has a square size of 6x6 tiles. Tile size is 32*32 pixels as defined in MINIMAP_TILE_SIZE.
 * If the pixel is outside of the map, it will be drawn as black.
 * If the pixel is inside of the map, it will be drawn as 0xFFFFFFFF.
 * If the pixel is inside of the map and it is a wall, it will be drawn as 0x008000FF.
*/

// void draw_minimap_visibile(t_cub3d *cub3d)
// {
//     double sq_start_x;
//     double sq_start_y;
//     double sq_end_x;
//     double sq_end_y;
//     size_t x = 0;
//     size_t y = 0;

//     sq_start_x = cub3d->P->mini_x - MINIMAP_VS / 2;
//     sq_start_y = cub3d->P->mini_y - MINIMAP_VS / 2;

//     sq_end_x = cub3d->P->mini_x + MINIMAP_VS / 2;
//     sq_end_y = cub3d->P->mini_y + MINIMAP_VS / 2;

//     while (sq_start_y < sq_end_y)
//     {
//         while (sq_start_x < sq_end_x)
//         {
//             // draw the player if met
//             if (sq_start_x == cub3d->P->mini_x && sq_start_y == cub3d->P->mini_y)
//             {
//                 draw_player(cub3d);
//                 x += PLAYER_SIZE;
//                 sq_start_x += PLAYER_SIZE;
//                 y += PLAYER_SIZE - 1;
//                 sq_start_y += PLAYER_SIZE - 1;
//                 continue;
//             }
//             // check if the pixel is outside of the map
//             if (sq_start_y < 0 || sq_start_x < 0 || sq_start_y >= cub3d->minimap->h_tiles * MINIMAP_TILE_SIZE || sq_start_x >= cub3d->minimap->w_tiles * MINIMAP_TILE_SIZE)
//             {
//                 mlx_put_pixel(cub3d->img, x, y, 0x000000FF); //black
//             }
//             // check if the pixel is inside of the map and it is not a wall
//             else if (cub3d->minimap->map[(int)(sq_start_y / MINIMAP_TILE_SIZE)][(int)(sq_start_x / MINIMAP_TILE_SIZE)] == 0)
//             {
//                 mlx_put_pixel(cub3d->img, x, y, 0xFFFFFFFF); //white
//             }
//             // check if the pixel is inside of the map and it is a wall
//             else
//             {
//                 mlx_put_pixel(cub3d->img, x, y, 0x008000FF); //green
//             }
//             x++;
//             sq_start_x++;
//         }
//         sq_start_x = cub3d->P->mini_x - MINIMAP_VS / 2;
//         sq_start_y++;
//         x = 0;
//         y++;
//     }
// }