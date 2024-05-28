/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:13:44 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 15:32:37 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>
/**
 * @struct t_vec
 * @brief Represents a 2D vector with x and y coordinates with double types.
 *
 * This structure is used to store 2D coordinates in the form of a vector.
 * The x and y members represent the x and y coordinates respectively.
 */
typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

/**
 * @struct t_vec_int
 * @brief Represents a 2D vector with x and y coordinates with int types.
 *
 * This structure is used to store 2D coordinates in the form of a vector.
 * The x and y members represent the x and y coordinates respectively.
 */
typedef struct s_vec_int
{
	int			x;
	int			y;
}				t_vec_int;

/**
 * @brief Converts a radian angle to it's equivalent vector representation.
 *
 * @param angle The angle in radians.
 * @return The noramlized direction vector.
 */
t_vec			angle_to_vec(double angle);

/**
 * Adds two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
t_vec			vec_add(t_vec a, t_vec b);

/**
 * Adds two integer vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
t_vec_int		vec_int_add(t_vec_int a, t_vec_int b);

/**
 * Subtracts two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The difference between the two vectors.
 */
t_vec			vec_sub(t_vec a, t_vec b);

/**
 * Scales a vector (type double) by a scalar value (multiplication).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec			vec_scal_m(t_vec a, double scalar);

/**
 * Scales an integer vector by a scalar value (multiplication).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec_int		vec_int_scal_m(t_vec_int a, double scalar);

/**
 * Scales a vector by a scalar value (division).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec			vec_scal_d(t_vec a, double scalar);

/**
 * Scales an integer vector by a scalar value (division).
 *
 * @param a The vector to be scaled.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec_int		vec_int_scal_d(t_vec a, double scalar);

/**
 * Calculates the dot product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
double			vec_dot(t_vec a, t_vec b);

/**
 * Calculates the length (magnitude) of a vector.
 *
 * @param a The vector.
 * @return The length of the vector.
 */
double			vec_len(t_vec a);

/**
 * Normalizes a vector (makes it a unit vector).
 *
 * @param a The vector to be normalized.
 * @return The normalized vector.
 */
t_vec			vec_normalize(t_vec a);

/**
 * Rotates a vector by a given angle (in radians).
 *
 * @param a The vector to be rotated.
 * @param angle The angle of rotation (in radians).
 * @return The rotated vector.
 */
t_vec			vec_rotate(t_vec a, double angle);

/**
 * Calculates the distance between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The distance between the two vectors.
 */
double			vec_distance(t_vec a, t_vec b);

/**
 * Inverts the given vector.
 *
 * @param a The vector to be inverted.
 * @return The inverted vector.
 */
t_vec			vec_inv(t_vec a);

/**
 * @param[in] double
 * @param[out] double
 * @brief Function pointer for mathematical functions applied to vectors.
 */
typedef double	(*t_vec_func)(double);

/**
 * Applies a mathematical function to each component of a vector.
 *
 * @param a The vector.
 * @param f The mathematical function to be applied.
 * @return The vector with the function applied to each component.
 */
t_vec			vec_apply(t_vec a, t_vec_func f);

#endif
