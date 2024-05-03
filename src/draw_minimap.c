#include "../includes/cub3d.h"

/* in this file I want to draw a minimap, draw a play and the direction of the player
 the main function is called draw_minimap that will be called 
 in a mlx_loop from main function.
 draw_minimap will call draw_player, draw_minimap and draw_player_direction and move_player functions
*/ 

// draw a pixel in the minimap

void draw_minimap(t_cub3d *cub3d)
{
	for (size_t y = 0; y < cub3d->minimap->h_pixels; y++)
	{
		for (size_t x = 0; x < cub3d->minimap->w_pixels; x++)
		{
			if (cub3d->minimap->map[(int) y / TILE_SIZE][(int) x / TILE_SIZE] > 0)
			{
				mlx_put_pixel(cub3d->img, x, y, 0x008000FF);
			}
			else
				mlx_put_pixel(cub3d->img, x, y, 0xFFFFFFFF);
			if (x % TILE_SIZE == 0 || y % TILE_SIZE == 0 || x == cub3d->minimap->w_pixels - 1 || y == cub3d->minimap->h_pixels - 1)
			{
				mlx_put_pixel(cub3d->img, x, y, 0xFFAEAEAE);
			}
		}
	}
}

void draw_player(t_cub3d *cub3d)
{
    for (int i = - PLAYER_SIZE / 2; i < PLAYER_SIZE / 2; i++)
    {
        for (int j = - PLAYER_SIZE / 2; j < PLAYER_SIZE / 2; j++)
        {
            mlx_put_pixel(cub3d->img, cub3d->P->mini_x + i, cub3d->P->mini_y + j, 0xFF0000FF); //red
            j++;
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
    for (int i = -1; i < steps; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            for (int k = -1; k < 2; k++)
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
    double x = cub3d->P->mini_x;
    double y = cub3d->P->mini_y;
    double x2 = x + cos(cub3d->P->dir) * (PLAYER_SIZE + 5);
    double y2 = y + sin(cub3d->P->dir) * (PLAYER_SIZE + 5);
    draw_line(cub3d->img, x, y, x2, y2, 0xFF0000FF); //black
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
