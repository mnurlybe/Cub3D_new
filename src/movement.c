#include "../includes/cub3d.h"

/*
In this file the handling of the player movement will be done, by implementing KEY_PRESS and KEY_RELEASE events.
The player will be able to move forward, backward, rotate left and right.
The direction_line should be drawn to show the direction/rotation of the player.
The handle_movement function will be called in the mlx_loop_hook function.
*/

void update_direction(t_cub3d *cub3d, double direction)
{
    cub3d->P->angle += direction;
    if (cub3d->P->angle < 0)
        cub3d->P->angle += 2 * M_PI;
    else if (cub3d->P->angle > 2 * M_PI)
        cub3d->P->angle -= 2 * M_PI;
    cub3d->P->dir = angle_to_vec(cub3d->P->angle);
}

void rotation(t_cub3d *cub3d)
{
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
        update_direction(cub3d, -PLAYER_ROT_SPEED);
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
        update_direction(cub3d, PLAYER_ROT_SPEED);
}

t_vec    wallslide(t_cub3d *cub3d, double angle)
{
    t_vec new_dir1 = {.x = 0, .y = cub3d->P->dir.y};
    t_vec new_dir2 = {.x = cub3d->P->dir.x, .y = 0};
    t_vec new_pos1 = vec_add(cub3d->P->pos, vec_scal_m(vec_rotate(new_dir1, angle), PLAYER_SPEED));
    t_vec new_pos2 = vec_add(cub3d->P->pos, vec_scal_m(vec_rotate(new_dir2, angle), PLAYER_SPEED));
    if (!is_wall(cub3d->minimap->map, new_pos1))
        return (new_pos1);
    else if (!is_wall(cub3d->minimap->map, new_pos2))
        return (new_pos2);
    else
        return (cub3d->P->pos);
}

void    update_position(t_cub3d *cub3d, double angle)
{
    t_vec new_pos;

    // The new position is calculated by adding the current position vector with the direction vector (normalized to 1 pixel) of the player multiplied by the speed
    new_pos = vec_add(cub3d->P->pos, vec_scal_m(vec_rotate(cub3d->P->dir, angle), PLAYER_SPEED));
    if (!is_wall(cub3d->minimap->map, new_pos))
        cub3d->P->pos = new_pos;
    else
        cub3d->P->pos = wallslide(cub3d, angle);
}

void move_player(t_cub3d *cub3d)
{
    // add check if the player is colliding with the wall, if so, do not move
    // also consider size of the player, as the player is a square of size 20, so no parts of the square should be inside the wall
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
        update_position(cub3d, 0);
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
        update_position(cub3d, - M_PI);
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
        update_position(cub3d, M_PI_2);
    if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
        update_position(cub3d, - M_PI_2);
}

void handle_movement(void *ptr)
{
    t_cub3d *cub3d = (t_cub3d *)ptr;

    // update rotation
    rotation(cub3d);
    // update the position based on the forward/backward movement
    move_player(cub3d);
}
