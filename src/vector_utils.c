/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:57:53 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/10 17:14:09 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec_int	vec_int_add(t_vec_int a, t_vec_int b)
{
	t_vec_int	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vec	vec_scal_m(t_vec a, double scalar)
{
	t_vec	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}

t_vec_int	vec_int_scal_m(t_vec a, double scalar)
{
	t_vec_int	result;

	result.x = (int) (a.x * scalar);
	result.y = (int) (a.y * scalar);
	return (result);
}

t_vec_int	vec_int_scal_d(t_vec a, double scalar)
{
	t_vec_int	result;

	result.x = (int) (a.x / scalar);
	result.y = (int) (a.y / scalar);
	return (result);
}

t_vec	vec_scal_d(t_vec a, double scalar)
{
	t_vec	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	return (result);
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec_len(t_vec a)
{
	return (sqrt(vec_dot(a, a)));
}

t_vec	vec_normalize(t_vec a)
{
	return (vec_scal_d(a, vec_len(a)));
}

t_vec	vec_rotate(t_vec a, double angle)
{
	t_vec	result;

	double cos_angle = cos(angle);
	double sin_angle = sin(angle);

	result.x = a.x * cos_angle - a.y * sin_angle;
	result.y = a.x * sin_angle + a.y * cos_angle;
	return (result);
}

t_vec vec_apply(t_vec a, vec_func f)
{
  t_vec result;

  result.x = f(a.x);
  result.y = f(a.y);
  return (result);
}
