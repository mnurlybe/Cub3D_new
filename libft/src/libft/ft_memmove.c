/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:55:39 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:15:37 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

/*
 *	Copies {n} bytes from memory area {src} to memory area {dest}. 
 *	The memory areas may overlap!
 *	Returns a pointer to {dest}.
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
		while (n--)
			*(d + n) = *(s + n);
	else
	{
		while (i < n)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	return (dest);
}
