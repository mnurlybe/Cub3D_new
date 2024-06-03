/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_int_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:57:53 by lwoiton           #+#    #+#             */
/*   Updated: 2024/06/03 17:07:34 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec_int	vec_int_add(t_vec_int a, t_vec_int b)
{
	t_vec_int	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec_int	vec_int_scal_m(t_vec_int a, double scalar)
{
	t_vec_int	result;

	result.x = (int)(a.x * scalar);
	result.y = (int)(a.y * scalar);
	return (result);
}

t_vec_int	vec_int_scal_d(t_vec a, double scalar)
{
	t_vec_int	result;

	result.x = (int)(a.x / scalar);
	result.y = (int)(a.y / scalar);
	return (result);
}
