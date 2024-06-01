/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:14:24 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:14:26 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_putstr_utils(char *str, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putspace(int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_putzero(int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (1, "0", 1);
		i++;
	}
	return (i);
}

int	ft_putsigns(t_flags *flags, t_specifiers *sp)
{
	if ((sp->d || sp->i) && flags->is_negative)
		return (ft_putstr_utils("-", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_space)
		return (ft_putstr_utils(" ", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_plus)
		return (ft_putstr_utils("+", 1));
	return (0);
}
