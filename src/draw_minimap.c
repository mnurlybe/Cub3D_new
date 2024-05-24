#include "../includes/cub3d.h"

/* in this file I want to draw a minimap, draw a play and the direction of the player
 the main function is called draw_minimap that will be called 
 in a mlx_loop from main function.
 draw_minimap will call draw_player, draw_minimap and draw_player_direction and move_player functions
*/ 

// draw a pixel in the minimap

void draw_minimap(t_cub3d *cub3d)
{
    size_t x = 0;
    size_t y = 0;
    while (y < cub3d->minimap->h_pixels)
    {
        while (x < cub3d->minimap->w_pixels)
        {
            if (cub3d->minimap->map[y / TILE_SIZE][x / TILE_SIZE] > 0)
                mlx_put_pixel(cub3d->img, x, y, GREEN);
            else
                mlx_put_pixel(cub3d->img, x, y, WHITE);
            if (x % TILE_SIZE == 0 || y % TILE_SIZE == 0 || x == cub3d->minimap->w_pixels - 1 || y == cub3d->minimap->h_pixels - 1)
                mlx_put_pixel(cub3d->img, x, y, BLACK);
            x++;
        }
        x = 0;
        y++;
    }
}

void draw_player(t_cub3d *cub3d)
{
    int delta_x;
    int delta_y;
    int x;
    int y;

    delta_x = - PLAYER_SIZE / 2;
    delta_y = - PLAYER_SIZE / 2;
    while (delta_x <= PLAYER_SIZE / 2)
    {
        x = delta_x + cub3d->P->pos.x;
        while (delta_y <= PLAYER_SIZE / 2)
        {
            if (delta_x * delta_x + delta_y * delta_y <= PLAYER_SIZE * PLAYER_SIZE / 4 + 1)
            {
                y = delta_y + cub3d->P->pos.y;
                mlx_put_pixel(cub3d->img, x, y, PLAYER_COLOR);
            }
            delta_y++;
        }
        delta_y = - PLAYER_SIZE / 2;
        delta_x++;
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
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while(i < steps)
    {
        j = 0;
        while(j < 3)
        {
            k = 0;
            while(k < 3)
            {
                mlx_put_pixel(img, x + j, y + k, color);
                k++;
            }
            j++;
        }
        x += xinc;
        y += yinc;
        i++;
    }
}

void draw_player_direction(t_cub3d *cub3d)
{
    double x = cub3d->P->pos.x + cos(cub3d->P->angle) * PLAYER_SIZE;
    double y = cub3d->P->pos.y + sin(cub3d->P->angle) * PLAYER_SIZE;
    draw_line(cub3d->img, cub3d->P->pos.x, cub3d->P->pos.y, x, y, PLAYER_COLOR); //black
}

void draw_map(void *ptr)
{
    t_cub3d *cub3d = (t_cub3d *)ptr;
    // draw the map
    draw_minimap(cub3d);
    // draw the player
    draw_player(cub3d);
    // draw the player direction
    draw_player_direction(cub3d);
}

// light green in hex
// 0x00FF00FF
// dark green in hex
// 0x008000FF
