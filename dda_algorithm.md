# Cub3D Raycasting Documentation
## Digital Differential Analysis (DDA) Implementation

### Table of Contents
1. [Introduction](#introduction)
2. [Resources](#resources)
3. [Mathematical Foundation](#mathematical-foundation)
4. [Core Concepts](#core-concepts)
5. [Implementation Details](#implementation-details)
7. [Optimization Techniques](#optimization-techniques)

## Introduction
This document details the implementation of the DDA (Digital Differential Analysis) algorithm in our Cub3D project, a raycasting engine inspired by Wolfenstein 3D. The DDA algorithm is used for efficient ray-wall collision detection in a grid-based environment.

## Resources

### Primary Resources
1. **Pikuma's DDA Mathematical Deep Dive**
   - URL: https://www.youtube.com/watch?v=NbSee-XM7WA
   - Critical contributions:
     - Thorough mathematical explanation of DDA in a grid system
     - Visual representation of step-by-step ray traversal
     - Clear explanation of horizontal vs vertical intersections
     - Precise mathematical formulas for distance calculations
     - Understanding of the relationship between ray direction and step calculations

2. **Lodev's Raycasting Tutorial**
   - URL: https://lodev.org/cgtutor/raycasting.html
   - Key concepts adapted: 
     - Basic DDA implementation
     - Wall collision detection
     - Texture mapping techniques

3. **3DSage's Raycasting Tutorial Series**
   - URL: https://www.youtube.com/watch?v=gYRrGTC7GtA
   - Contributions: 
     - Visual understanding of ray intersection mechanics
     - Real-time implementation concepts

4. **Wikipedia - Ray Casting**
   - URL: https://en.wikipedia.org/wiki/Ray_casting
   - Theoretical foundation and mathematical concepts

### Additional Resources
5. **Computer Graphics Principles**
   - "Fundamentals of Computer Graphics" by Marschner & Shirley
   - DDA line drawing algorithm foundations

6. **Game Engine Architecture**
   - "Game Engine Architecture" by Jason Gregory
   - Spatial partitioning and grid-based collision detection

## Mathematical Foundation

### Vectors in DDA

The implementation of vectors in the DDA algorithm is crucial for efficient and accurate raycasting. Vectors allow for the representation of direction and magnitude, which are essential for calculating ray directions, distances, and intersections within a cartesian coordinate system (the window) and espacially our grid. By using vector operations, we can simplify and optimize the mathematical computations involved in the DDA process. For a detailed explanation of the vector implementation and its benefits, refer to the [Vectors Documentation](vectors.md).

### Grid Intersection Mathematics (Based on Pikuma's Explanation)

#### 1. Ray Direction Components
```c
// Ray direction vector calculation
ray.dir.x = cos(ray_angle)
ray.dir.y = sin(ray_angle)
```

#### 2. Delta Distance Calculation
The delta distance represents how far along the ray we need to move to cross one grid cell:
```c
// Delta distances (distance between consecutive x or y intersections)
delta_dist.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x))
delta_dist.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y))

// Optimized version
delta_dist.x = fabs(1 / ray.dir.x)
delta_dist.y = fabs(1 / ray.dir.y)
```

#### 3. Initial Step Distance
Calculate the distance to the first grid intersection:
```c
// Step and initial side distance calculation
if (ray.dir.x < 0) {
    step.x = -1;
    side_dist.x = (player.x - map.x) * delta_dist.x;
} else {
    step.x = 1;
    side_dist.x = (map.x + 1.0 - player.x) * delta_dist.x;
}

if (ray.dir.y < 0) {
    step.y = -1;
    side_dist.y = (player.y - map.y) * delta_dist.y;
} else {
    step.y = 1;
    side_dist.y = (map.y + 1.0 - player.y) * delta_dist.y;
}
```

### Key Mathematical Insights from Pikuma

1. **Grid Alignment**
   - The DDA algorithm works by tracking the nearest grid intersection points
   - Horizontal and vertical intersections are handled separately but in parallel

2. **Distance Comparison**
   ```c
   // Determines which grid line we intersect first
   if (side_dist.x < side_dist.y) {
       side_dist.x += delta_dist.x;
       map_x += step_x;
       side = 0; // Vertical intersection
   } else {
       side_dist.y += delta_dist.y;
       map_y += step_y;
       side = 1; // Horizontal intersection
   }
   ```

3. **Perpendicular Distance Calculation**
   ```c
   // Calculate perpendicular distance to avoid fisheye effect
   if (side == 0)
       perp_wall_dist = (map_x - player.x + (1 - step_x) / 2) / ray.dir.x;
   else
       perp_wall_dist = (map_y - player.y + (1 - step_y) / 2) / ray.dir.y;
   ```

## Implementation Details

### DDA Core Algorithm
```c
void cast_ray(t_cub3d *cub3d, t_ray *ray)
{
    t_vec delta_dist;
    t_vec distance;

    // Calculate delta_dist using optimized formula from Pikuma
    delta_dist = vec_apply(vec_inv(ray->dir), fabs);
    
    // Calculate initial offset (incorporating Pikuma's grid alignment concept)
    distance = calculate_initial_offset(cub3d, ray, delta_dist);
    
    // Perform DDA
    dda(cub3d, ray, delta_dist, &distance);
    
    // Determine final distance and wall hit point
    if (vertical_gridline_hit(&distance))
        ray->distance = distance.x;
    else
        ray->distance = distance.y;
        
    // Calculate exact wall hit point
    ray->wall_hit = vec_add(cub3d->p->pos, 
                           vec_scal_m(ray->dir, ray->distance));
                           
    // Apply fisheye correction (from Pikuma's insights)
    ray->distance *= cos(cub3d->p->angle - ray->angle);
}
```

## Optimization Techniques

### 1. Integer Grid Traversal
- Using integer arithmetic for grid position tracking
- Avoiding floating-point operations where possible

### 2. Early Exit Conditions
- Breaking loop immediately upon wall hit
- Checking map boundaries efficiently

### 3. Vector Operations
- Pre-calculated direction vectors
- Optimized distance calculations

### 4. Memory Management
- Efficient struct packing
- Minimal memory allocations during raycast

## Performance Considerations

### Critical Sections
1. **Ray Casting Loop**
   - Most computationally intensive part
   - Optimized for minimal calculations per iteration

2. **Distance Calculations**
   - Uses pre-calculated values where possible
   - Minimizes trigonometric operations

### Bottlenecks to Consider
1. **Texture Mapping**
   - Memory access patterns
   - Cache considerations

2. **Floating Point Operations**
   - Balance between precision and performance
   - Strategic use of fixed-point arithmetic

## Future Improvements

### Potential Enhancements
1. **SIMD Instructions**
   - Vectorize ray calculations
   - Parallel processing of multiple rays

2. **Spatial Partitioning**
   - BSP trees for larger maps
   - Octree implementation for complex scenes

3. **Multi-threading**
   - Parallel ray processing
   - Load balancing strategies

## Testing Methodology

### Visual Verification
1. **Grid Line Detection**
   - Visualization of ray-grid intersections
   - Debugging overlay for ray paths

2. **Distance Accuracy**
   - Testing at various angles
   - Wall perpendicular distance verification

### Performance Testing
1. **FPS Monitoring**
   - Baseline performance metrics
   - Optimization impact measurement

2. **Edge Cases**
   - Corner cases handling
   - Extreme angle testing