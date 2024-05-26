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

void render_wall(t_cub3d *cub3d, t_ray *ray)
{
	int delta_height = (int) (cub3d->height / ray->distance);
	int start = (cub3d->height - delta_height) / 2;
	int end = start + delta_height;

	int tex_num = ray->side;
	double wallX = (ray->side == NORTH || ray->side == SOUTH) ? ray->wall_hit.x : ray->wall_hit.y;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)cub3d->textures[tex_num]->width);
	for (int y = start; y < end; y++)
	{
	   int texY = ((y - start) * cub3d->textures[tex_num]->height) / delta_height;
		 texY = texY % cub3d->textures[tex_num]->height;  // Handle wrapping
		 uint32_t color = get_pixel_color(cub3d->textures[tex_num], texX, texY);
		 mlx_put_pixel(cub3d->buf, ray->index, y, color);
  }
}

/**
 * This function renders the floor and since the ceiling is symmetrical, 
 * we can just use the same code to render the ceiling
*  The rendering for the ceiling and floor is done before the walls. 
*  And instead of rendering going vertil stripe by vertical stripe, we go row by row.
*
*  The formula for rowDistance, the horizontal distance from camera to the floor 
*  for the current row, which is posZ / p with p the current pixel distance 
*  from the screen center, can be explained as follows:
*
*  The camera ray goes through the following two points: the camera itself, 
*  which is at a certain height (posZ), and a point in front of the camera 
*  (through an imagined vertical plane containing the screen pixels) with 
*  horizontal distance 1 from the camera, and vertical position p lower than 
*  posZ (posZ - p). When going through that point, the line has vertically 
*  traveled by p units and horizontally by 1 unit. To hit the floor, it instead needs
*  to travel by posZ units. It will travel the same ratio horizontally. 
*  The ratio was 1 / p for going through the camera plane, so to go posZ times 
*  farther to reach the floor, we get that the total horizontal distance is posZ / p. 
*
 * @cub3d: A pointer to the t_cub3d structure containing all game and rendering context.
 *        This includes player position, viewing angles, screen dimensions, textures, and more.
 * @fov_rad: The field of view in radians, specifying the horizontal extent of the visible world.
 */
void render_ceiling_floor(t_cub3d *cub3d, double fov_rad)
{
  
  double pos_z = 0.5 * cub3d->height;
  t_vec ray_min = angle_to_vec(cub3d->P->angle - fov_rad / 2);
  t_vec ray_max = angle_to_vec(cub3d->P->angle + fov_rad / 2);
  for (int y = (int) cub3d->height / 2; y < (int) cub3d->height; y++)
  {
    int p = y - cub3d->height / 2;
    double row_distance = pos_z / p;
    t_vec floor_step = vec_scal_d(vec_scal_m(vec_sub(ray_max, ray_min), row_distance), (double) cub3d->width);
    t_vec floor = vec_add(cub3d->P->pos, vec_scal_m(ray_min, row_distance));
    for (int x = 0; x < (int) cub3d->width; x++)
    {
      t_vec_int cell = {(int) floor.x, (int) floor.y};
      int tx = (int) (cub3d->textures[FLOOR]->width * (floor.x - cell.x)) & (cub3d->textures[FLOOR]->width - 1);
      int ty = (int) (cub3d->textures[FLOOR]->height * (floor.y - cell.y)) & (cub3d->textures[FLOOR]->height - 1);
      uint32_t floor_color = get_pixel_color(cub3d->textures[FLOOR], tx, ty);
      uint32_t ceiling_color = get_pixel_color(cub3d->textures[CEILING], tx, ty);
      mlx_put_pixel(cub3d->buf, x, y, floor_color);
      if (cub3d->height - y - 1 < 0 || cub3d->height - y - 1 >= cub3d->height)
        printf("(% d | %d) %d\n", x , (int) cub3d->height - y - 1);
      mlx_put_pixel(cub3d->buf, x, cub3d->height - y - 1, ceiling_color);
      floor = vec_add(floor, floor_step);
    }
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
  render_ceiling_floor(cub3d, fov_rad);
  while (ray.index < (int) cub3d->width)
  {
    ray.angle = cub3d->P->angle -  fov_rad / 2 + ray.index * ray_inc;
    ray.dir = angle_to_vec(ray.angle);
    cast_ray(cub3d, &ray);
    render_wall(cub3d, &ray);
    ray.index++;
  }
}
