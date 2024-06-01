/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:14:15 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:14:17 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_putstr_utils_fd(int fd, char *str, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putspace_fd(int fd, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (fd, " ", 1);
		i++;
	}
	return (i);
}

int	ft_putzero_fd(int fd, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write (fd, "0", 1);
		i++;
	}
	return (i);
}

int	ft_putsigns_fd(int fd, t_flags *flags, t_specifiers *sp)
{
	if ((sp->d || sp->i) && flags->is_negative)
		return (ft_putstr_utils_fd(fd, "-", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_space)
		return (ft_putstr_utils_fd(fd, " ", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_plus)
		return (ft_putstr_utils_fd(fd, "+", 1));
	return (0);
}
