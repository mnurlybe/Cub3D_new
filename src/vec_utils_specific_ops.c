/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_specific_ops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:57:53 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 15:32:42 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec	angle_to_vec(double angle)
{
	t_vec	result;

	result.x = cos(angle);
	result.y = sin(angle);
	return (result);
}

t_vec	vec_rotate(t_vec a, double angle)
{
	t_vec	result;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	result.x = a.x * cos_angle - a.y * sin_angle;
	result.y = a.x * sin_angle + a.y * cos_angle;
	return (result);
}

t_vec	vec_inv(t_vec a)
{
	t_vec	result;

	result.x = 1 / a.x;
	result.y = 1 / a.y;
	return (result);
}

t_vec	vec_apply(t_vec a, t_vec_func f)
{
	t_vec	result;

	result.x = f(a.x);
	result.y = f(a.y);
	return (result);
}
