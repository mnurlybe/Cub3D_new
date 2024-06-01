/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:14:11 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:14:13 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	ft_init_flags(t_flags *flags)
{
	flags->is_negative = 0;
	flags->is_dash = 0;
	flags->is_zero = 0;
	flags->is_dot = 0;
	flags->is_hash = 0;
	flags->is_space = 0;
	flags->is_plus = 0;
	flags->width = 0;
	flags->pr_width = 0;
}

void	ft_init_specifiers(t_specifiers *sp)
{
	sp->c = 0;
	sp->s = 0;
	sp->d = 0;
	sp->i = 0;
	sp->u = 0;
	sp->x = 0;
	sp->xcap = 0;
	sp->p = 0;
	sp->percent = 0;
}

void	ft_init(t_flags *f, t_specifiers *sp)
{
	ft_init_flags(f);
	ft_init_specifiers(sp);
}
