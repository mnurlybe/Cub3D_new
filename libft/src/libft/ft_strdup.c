/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:15:52 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/06/01 17:15:37 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

/*
 *	This function returns a pointer to a null-terminated byte string,
 *	which is a duplicate of the string pointed to by {s}. 
 *	The memory obtained is done dynamically using malloc 
 *	and hence it can be freed using free(). 
*/
char	*ft_strdup(const char *s)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (i <= len)
	{
		*(new_str + i) = (char )s[i];
		i++;
	}
	*(new_str + len) = 0;
	return (new_str);
}
