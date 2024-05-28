/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_basic_ops.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:57:53 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 15:12:46 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	result;

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

t_vec	vec_scal_d(t_vec a, double scalar)
{
	t_vec	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	return (result);
}
