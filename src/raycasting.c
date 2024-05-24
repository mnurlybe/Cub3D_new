#include "../includes/cub3d.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

double  deg_to_rad(double angle)
{
  return (angle * M_PI / 180);
}

int is_zero(double value)
{
  return (fabs(value) < 1e-10);
}

void calculate_initial_offset(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist, t_vec_int map,t_vec *offset)
{
  t_vec p;

  p = cub3d->P->pos;
  if (ray->dir.x < 0)
    offset->x = (p.x - map.x * TILE_SIZE) * delta_dist.x;
  else
    offset->x = ((map.x + 1) * TILE_SIZE - p.x) * delta_dist.x;
  if (ray->dir.y < 0)
    offset->y = (p.y - map.y * TILE_SIZE) * delta_dist.y;
  else
    offset->y = ((map.y + 1) * TILE_SIZE - p.y) * delta_dist.y;
}

bool vertical_gridline_hit(t_vec *d)
{
  return ((d->x < d->y && !is_zero(d->x)) || is_zero(d->y));
}

int  is_tile_wall(t_cub3d *cub3d, t_ray *ray, t_vec_int map, int wall_type)
{
  ray->wall = cub3d->minimap->map[map.y][map.x];
  if (ray->wall == 0)
    return (ray->wall);
  if (wall_type == 1)
  {
    if (ray->dir.x > 0)
      ray->side = EAST;
    else
      ray->side = WEST;
  }
  else if (wall_type == 0)
  {
    if (ray->dir.y > 0)
      ray->side = SOUTH;
    else
      ray->side = NORTH;
  }
  return (ray->wall);
}

void  dda(t_cub3d *cub3d, t_ray *ray, t_vec delta_dist, t_vec_int map, t_vec *distance)
{
  t_vec_int step = {(ray->dir.x < 0) ? -1 : 1, (ray->dir.y < 0) ? -1 : 1};
  while (true)
  {
    if (vertical_gridline_hit(distance))
    {
      map.x += step.x;
      if (is_tile_wall(cub3d, ray, map, 1))
        break;
      distance->x += delta_dist.x * TILE_SIZE;
    }
    else
    {
      map.y += step.y;
      if (is_tile_wall(cub3d, ray, map, 0))
        break;
      distance->y += delta_dist.y * TILE_SIZE;
    }
  }
}

void cast_ray(t_cub3d *cub3d, t_ray *ray)
{
  t_vec delta_dist = {fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
  t_vec distance;

  t_vec_int map = {cub3d->P->pos.x / TILE_SIZE, cub3d->P->pos.y / TILE_SIZE};
  calculate_initial_offset(cub3d, ray, delta_dist, map, &distance);
  dda(cub3d, ray, delta_dist, map, &distance);
  if (vertical_gridline_hit(&distance))
    ray->distance = distance.x;
  else
    ray->distance = distance.y;
  ray->distance *= cos(cub3d->P->angle - ray->angle);
  ray->wall_hit = vec_add(cub3d->P->pos, vec_scal_m(ray->dir, ray->distance));
}

uint32_t get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	uint32_t *pixels = (uint32_t *)texture->pixels;
	return (pixels[y * texture->width + x]);
}

void render_ray(t_cub3d *cub3d, t_ray *ray)
{
	int delta_height = (int) (cub3d->height / ray->distance);
	int start = (cub3d->height - delta_height) / 2;
	int end = start + delta_height;

	int tex_num = ray->side;
	// Calculate exact position on the wall texture
  double wallHitX = ray->wall_hit.x;
  double wallHitY = ray->wall_hit.y;

	// Correct texture coordinates based on wall side
	double wallX = (ray->side == NORTH || ray->side == SOUTH) ? wallHitX : wallHitY;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)cub3d->textures[tex_num]->width);
	for (int y = 0; y < (int) cub3d->height; y++)
	{
		if (y >= start && y <= end)
		{
		    int texY = ((y - start) * cub3d->textures[tex_num]->height) / delta_height;
		    texY = texY % cub3d->textures[tex_num]->height;  // Handle wrapping
		    uint32_t color = get_pixel_color(cub3d->textures[tex_num], texX, texY);
		    mlx_put_pixel(cub3d->buf, ray->index, y, color);
		}
		else if (y < start)
			mlx_put_pixel(cub3d->buf, ray->index, y, 0x00FFFFFF);
		else
			mlx_put_pixel(cub3d->buf, ray->index, y, 0xFF000000);
  }
}

void  cast_fov(void *ptr)
{
  t_cub3d *cub3d;
  t_ray ray;

  cub3d = (t_cub3d *)ptr;
  double fov_rad = deg_to_rad(cub3d->P->fov);
  double ray_inc = fov_rad / cub3d->width;
  cub3d = (t_cub3d *)ptr;
  ray.index = 0;
  while (ray.index < (int) cub3d->width)
  {
    ray.angle = cub3d->P->angle -  fov_rad / 2 + ray.index * ray_inc;
    ray.dir = angle_to_vec(ray.angle);
    cast_ray(cub3d, &ray);
    render_ray(cub3d, &ray);
    ray.index++;
  }
}
