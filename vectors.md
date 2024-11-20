# Vector Implementation in Cub3D
## Understanding Vectors in a Cartesian Coordinate System

### Table of Contents
1. [Introduction](#introduction)
2. [Vector Implementation](#vector-implementation)
3. [Mathematical Operations](#mathematical-operations)
4. [Practical Applications](#practical-applications)
5. [Performance Considerations](#performance-considerations)

## Introduction

In our raycasting engine, vectors are fundamental mathematical tools that represent both position and direction in a 2D cartesian coordinate system. They are particularly useful because they:
- Provide a clean way to handle positions and directions
- Simplify mathematical operations
- Make the code more readable and maintainable
- Enable efficient geometric calculations

## Vector Implementation

### Basic Structures
We implement two types of vectors to handle different use cases:

```c
// Double precision vector for accurate calculations
typedef struct s_vec {
    double x;
    double y;
} t_vec;

// Integer vector for grid operations
typedef struct s_vec_int {
    int x;
    int y;
} t_vec_int;
```

### Core Vector Operations

1. **Basic Operations**
```c
// Vector addition
t_vec vec_add(t_vec a, t_vec b) {
    return (t_vec){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

// Vector subtraction
t_vec vec_sub(t_vec a, t_vec b) {
    return (t_vec){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

// Scalar multiplication
t_vec vec_scal_m(t_vec a, double scalar) {
    return (t_vec){
        .x = a.x * scalar,
        .y = a.y * scalar
    };
}
```

2. **Advanced Operations**
```c
// Vector length (magnitude)
double vec_len(t_vec a) {
    return sqrt(vec_dot(a, a));
}

// Dot product
double vec_dot(t_vec a, t_vec b) {
    return (a.x * b.x + a.y * b.y);
}

// Vector normalization
t_vec vec_normalize(t_vec a) {
    return vec_scal_d(a, vec_len(a));
}
```

## Mathematical Foundation in Cartesian Coordinates

### 1. Position Representation
In a cartesian system, vectors naturally represent:
- Player position: `t_vec pos = {x, y}`
- Ray endpoints: `t_vec wall_hit`
- Relative positions between objects

### 2. Direction Representation
Vectors efficiently encode direction information:
```c
// Convert angle to direction vector
t_vec angle_to_vec(double angle) {
    return (t_vec){
        .x = cos(angle),
        .y = sin(angle)
    };
}

// Rotate a vector by an angle
t_vec vec_rotate(t_vec a, double angle) {
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    return (t_vec){
        .x = a.x * cos_angle - a.y * sin_angle,
        .y = a.x * sin_angle + a.y * cos_angle
    };
}
```

## Practical Applications

### 1. Player Movement
```c
// Update player position based on direction and speed
void update_position(t_cub3d *cub3d, double angle) {
    t_vec new_pos = vec_add(
        cub3d->p->pos, 
        vec_scal_m(
            vec_rotate(cub3d->p->dir, angle), 
            PLAYER_SPEED
        )
    );
    
    // Check collision and update if valid
    if (!is_wall(cub3d->minimap->map, new_pos))
        cub3d->p->pos = new_pos;
}
```

### 2. Ray Casting
```c
// Calculate ray direction and initial position
void cast_ray(t_cub3d *cub3d, t_ray *ray) {
    // Convert angle to direction vector
    ray->dir = angle_to_vec(ray->angle);
    
    // Calculate delta distances using vector operations
    t_vec delta_dist = vec_apply(vec_inv(ray->dir), fabs);
    
    // Cast ray and find wall intersection
    t_vec wall_hit = vec_add(
        cub3d->p->pos,
        vec_scal_m(ray->dir, ray->distance)
    );
}
```

### 3. Collision Detection
```c
// Check if position is inside wall
int is_wall(int **map, t_vec pos) {
    return map[(int)(pos.y / TILE_SIZE)]
             [(int)(pos.x / TILE_SIZE)];
}
```

## Advantages in Cartesian Coordinates

1. **Intuitive Grid Mapping**
   - Direct mapping between vector coordinates and grid positions
   - Easy conversion between world and grid coordinates
   ```c
   t_vec_int grid_pos = vec_int_scal_d(world_pos, TILE_SIZE);
   ```

2. **Simplified Distance Calculations**
   - Euclidean distance using vector operations
   ```c
   double distance = vec_len(vec_sub(point_a, point_b));
   ```

3. **Efficient Movement Calculations**
   - Movement vectors can be scaled, rotated, and added
   - Collision checking becomes straightforward

4. **DDA Algorithm Integration**
   - Vector operations simplify ray step calculations
   - Clean handling of horizontal and vertical intersections

## Performance Considerations

1. **Memory Efficiency**
   - Compact representation of position and direction
   - Cache-friendly structure alignment

2. **Computational Efficiency**
   - Minimized trigonometric calculations
   - Optimized vector operations for common use cases
   ```c
   // Optimized distance calculation for DDA
   t_vec delta_dist = vec_apply(vec_inv(ray->dir), fabs);
   ```

3. **Type-Specific Optimizations**
   - Integer vectors for grid operations
   - Double precision vectors for accurate physics

## Best Practices

1. **Vector Normalization**
   - Normalize direction vectors after rotation
   - Maintain unit vectors for direction calculations

2. **Error Prevention**
   - Check for division by zero in vector operations
   - Handle edge cases in trigonometric calculations

3. **Code Organization**
   - Group related vector operations
   - Maintain consistent naming conventions
   - Document mathematical relationships

By implementing vectors in this way, we create a robust foundation for all geometric calculations in our raycasting engine, making the code both more maintainable and mathematically sound.

Would you like me to elaborate on any specific aspect of vector implementation or provide more examples of their practical use in the project?