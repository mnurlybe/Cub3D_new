/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:28:55 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/27 19:28:57 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_indexes(t_file *info)
{
	size_t	i;

	i = 0;
	while (i++ < info->file_size)
	{
		if (!is_only_whitespace(info->split_file[i])
			&& is_only_ones(info->split_file[i]))
		{
			info->map_start_index = i;
			break ;
		}
	}
	i++;
	while (i++ < info->file_size)
	{
		if ((!is_only_whitespace(info->split_file[i])
				&& is_only_ones(info->split_file[i])))
		{
			info->map_end_index = i;
			break ;
		}
	}
	if (info->map_start_index == -1 || info->map_end_index == -1)
		return (0);
	return (1);
}