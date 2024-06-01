/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_num_of_digits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:13:52 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:13:55 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

size_t	ft_find_nod(unsigned int num, int system)
{
	size_t	num_of_digits;

	num_of_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num_of_digits++;
		num /= system;
	}
	return (num_of_digits + 1);
}

size_t	ft_find_nod_l(unsigned long long num, int system)
{
	size_t	num_of_digits;

	(void)system;
	num_of_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num_of_digits++;
		num /= system;
	}
	return (num_of_digits + 1);
}
