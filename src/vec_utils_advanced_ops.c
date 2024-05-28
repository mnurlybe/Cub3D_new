/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_advanced_ops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:57:53 by lwoiton           #+#    #+#             */
/*   Updated: 2024/05/28 15:32:41 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	vec_distance(t_vec a, t_vec b)
{
	return (vec_len(vec_sub(a, b)));
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
