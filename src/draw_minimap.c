#include "../includes/cub3d.h"

/* in this file I want to draw a minimap, draw a play and the direction of the player
 the main function is called draw_minimap that will be called 
 in a mlx_loop from main function.
 draw_minimap will call draw_player, draw_minimap and draw_player_direction and move_player functions
*/ 

// draw a pixel in the minimap

void draw_map(t_cub3d *cub3d)
{
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            if (cub3d->minimap->map[y][x] == 1)
            {
                for (size_t i = 0; i < TILE_SIZE * MINIMAP_SCALE; i++)
                {
                    for (size_t j = 0; j < TILE_SIZE * MINIMAP_SCALE; j++)
                    {
                        mlx_put_pixel(cub3d->img, x * TILE_SIZE * MINIMAP_SCALE + i, y * TILE_SIZE * MINIMAP_SCALE + j, 0x008000FF); //green
                    }
                }
            }
            else
            {
                for (size_t i = 0; i < TILE_SIZE * MINIMAP_SCALE; i++)
                {
                    for (size_t j = 0; j < TILE_SIZE * MINIMAP_SCALE; j++)
                    {
                        mlx_put_pixel(cub3d->img, x * TILE_SIZE * MINIMAP_SCALE + i, y * TILE_SIZE * MINIMAP_SCALE + j, 0xFFFFFFFF); //white
                    }
                }
            }
        }
    }
}

void draw_player(t_cub3d *cub3d)
{
    for (size_t i = 0; i < PLAYER_SIZE; i++)
    {
        for (size_t j = 0; j < PLAYER_SIZE; j++)
        {
            mlx_put_pixel(cub3d->img, cub3d->P->mini_x + i, cub3d->P->mini_y + j, 0xFF0000FF); //red
        }
    }
}

// draw a thicker line starting in the middle of the player square
void draw_line(mlx_image_t *img, double x1, double y1, double x2, double y2, int color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = sqrt(dx * dx + dy * dy);
    double xinc = dx / steps;
    double yinc = dy / steps;
    double x = x1;
    double y = y1;
    for (size_t i = 0; i < steps; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                mlx_put_pixel(img, x + j, y + k, color);
            }
        }
        x += xinc;
        y += yinc;
    }
}

void draw_player_direction(t_cub3d *cub3d)
{
    double x = cub3d->P->mini_x + PLAYER_SIZE / 2;
    double y = cub3d->P->mini_y + PLAYER_SIZE / 2;
    double x2 = x + cos(cub3d->P->dir) * PLAYER_SIZE;
    double y2 = y + sin(cub3d->P->dir) * PLAYER_SIZE;
    draw_line(cub3d->img, x, y, x2, y2, 0xFF0000FF); //black
}

void draw_minimap(void *ptr)
{

    t_cub3d *cub3d = (t_cub3d *)ptr;

    // draw the map
    draw_map(cub3d);
    // draw the player
    draw_player(cub3d);
    // draw the player direction
    draw_player_direction(cub3d);
}

// light green in hex
// 0x00FF00FF
// dark green in hex
// 0x008000FF