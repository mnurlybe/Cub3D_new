#include "../includes/cub3d.h"

/**
 * the minimap will display only a fixed square size 128*128 pixels.
 * It will show only certain part of the map, where the player is seen in the center of the square.
*/

void draw_minimap_vis(t_cub3d *cub3d)
{
    double sq_start_x;
    double sq_start_y;
    double sq_end_x;
    double sq_end_y;
    double x;
    double y;

    sq_start_x = cub3d->P->pos.x - 64;
    sq_start_y = cub3d->P->pos.y - 64;
    sq_end_x = cub3d->P->pos.x + 64;
    sq_end_y = cub3d->P->pos.y + 64;
    x = 0;
    y = 0;

    while (sq_start_y < sq_end_y)
    {
        while (sq_start_x < sq_end_x)
        {
            // check if pixel outside the map
            if (sq_start_x < 0 || sq_start_y < 0 || sq_start_x >= cub3d->minimap->w_pixels || sq_start_y >= cub3d->minimap->h_pixels)
            {
                mlx_put_pixel(cub3d->buf, x, y, BLACK);
            }
            else
            {
                // check if pixel is a wall
                if (cub3d->minimap->map[(int)sq_start_y / TILE_SIZE][(int)sq_start_x / TILE_SIZE] > 0)
                    mlx_put_pixel(cub3d->buf, x, y, GREEN);
                else // if not a wall
                    mlx_put_pixel(cub3d->buf, x, y, WHITE);
            }
            x++;
            sq_start_x++;
        }
        sq_start_x = cub3d->P->pos.x - 64;
        x = 0;
        sq_start_y++;
        y++;
    }

}

void draw_player_vis(t_cub3d *cub3d)
{
    int delta_x;
    int delta_y;
    int x;
    int y;

    delta_x = - PLAYER_SIZE / 2;
    delta_y = - PLAYER_SIZE / 2;
    while (delta_x <= PLAYER_SIZE / 2)
    {
        x = delta_x + 64;
        while (delta_y <= PLAYER_SIZE / 2)
        {
            if (delta_x * delta_x + delta_y * delta_y <= PLAYER_SIZE * PLAYER_SIZE / 4 + 1)
            {
                y = delta_y + 64;
                mlx_put_pixel(cub3d->buf, x, y, PLAYER_COLOR);
            }
            delta_y++;
        }
        delta_y = - PLAYER_SIZE / 2;
        delta_x++;
    }
}

// draw a thicker line starting in the middle of the player square
void draw_line_vis(mlx_image_t *img, double x1, double y1, double x2, double y2, int color)
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

void draw_player_direction_vis(t_cub3d *cub3d)
{
    double x1;
    double y1;
    double x2;
    double y2;

    x1 = 64;
    y1 = 64;
    x2 = x1 + 8 * cos(cub3d->P->angle);
    y2 = y1 + 8 * sin(cub3d->P->angle);
    draw_line_vis(cub3d->buf, x1, y1, x2, y2, PLAYER_COLOR);
}

void draw_map_vis(void *ptr)
{
    t_cub3d *cub3d = (t_cub3d *)ptr;
    // draw the map
    draw_minimap_vis(cub3d);
    // draw the player
    draw_player_vis(cub3d);
    // draw the player direction
    draw_player_direction_vis(cub3d);
}