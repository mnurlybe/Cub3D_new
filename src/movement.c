#include "../includes/cub3d.h"

/*
In this file the handling of the player movement will be done, by implementing KEY_PRESS and KEY_RELEASE events.
The player will be able to move forward, backward, rotate left and right.
The direction_line should be drawn to show the direction/rotation of the player.
The handle_movement function will be called in the mlx_loop_hook function.
*/

void rotation(t_cub3d *cub3d)
{
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
    {
        cub3d->P->dir -= PLAYER_ROT_SPEED;
        if (cub3d->P->dir < 0)
            cub3d->P->dir += 2 * M_PI;
    }
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
    {
        cub3d->P->dir += PLAYER_ROT_SPEED;
        if (cub3d->P->dir > 2 * M_PI)
            cub3d->P->dir -= 2 * M_PI;
    }
//	printf("dir: %lf\n", cub3d->P->dir);
}

void move_player(t_cub3d *cub3d)
{
    double new_x;
    double new_y;
    // add check if the player is colliding with the wall, if so, do not move
    // also consider size of the player, as the player is a square of size 20, so no parts of the square should be inside the wall

    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
    {
        new_x = cub3d->P->mini_x + PLAYER_SPEED * cos(cub3d->P->dir);
        new_y = cub3d->P->mini_y + PLAYER_SPEED * sin(cub3d->P->dir);
        if (cub3d->minimap->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0)
        {
            cub3d->P->mini_x = new_x;
            cub3d->P->mini_y = new_y;
        }
    }
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
    {
        new_x = cub3d->P->mini_x - PLAYER_SPEED * cos(cub3d->P->dir);
        new_y = cub3d->P->mini_y - PLAYER_SPEED * sin(cub3d->P->dir);
        if (cub3d->minimap->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0)
        {
            cub3d->P->mini_x = new_x;
            cub3d->P->mini_y = new_y;
        }
    }
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
    {
        new_x = cub3d->P->mini_x - PLAYER_SPEED * cos(cub3d->P->dir + M_PI_2);
        new_y = cub3d->P->mini_y - PLAYER_SPEED * sin(cub3d->P->dir + M_PI_2);
        if (cub3d->minimap->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0)
        {
            cub3d->P->mini_x = new_x;
            cub3d->P->mini_y = new_y;
        }
    }
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
    {
        new_x = cub3d->P->mini_x + PLAYER_SPEED * cos(cub3d->P->dir + M_PI_2);
        new_y = cub3d->P->mini_y + PLAYER_SPEED * sin(cub3d->P->dir + M_PI_2);
        if (cub3d->minimap->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0)
        {
            cub3d->P->mini_x = new_x;
            cub3d->P->mini_y = new_y;
        }
    }
//	printf("ppos: (%5lf | %5lf)\n", cub3d->P->mini_x, cub3d->P->mini_y);	 
}

void handle_movement(void *ptr)
{
    t_cub3d *cub3d = (t_cub3d *)ptr;

    // update rotation
    rotation(cub3d);
    // update the position based on the forward/backward movement
    move_player(cub3d);
}
