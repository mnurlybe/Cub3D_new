/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:28:55 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 20:02:14 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_indexes(t_file *info)
{
	if (info->map_start_index == -1 || info->map_end_index == -1
		|| (info->map_end_index - info->map_start_index) < 2)
		return (0);
	else
		return (1);
}

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
	while (i < info->file_size)
	{
		if ((!is_only_whitespace(info->split_file[i])
				&& is_only_ones(info->split_file[i])))
		{
			info->map_end_index = i;
			break ;
		}
		i++;
	}
	return (check_indexes(info));
}

int	check_map(t_file *info)
{
	size_t	i;

	i = info->map_start_index;
	while ((int)i++ < info->map_end_index)
	{
		if (is_only_whitespace(info->split_file[i])
			|| !is_only_allowed_chars(info->split_file[i]))
			return (0);
	}
	i++;
	while (i < info->file_size)
	{
		if (!is_only_whitespace(info->split_file[i]))
			return (0);
		i++;
	}
	i = info->map_start_index;
	while ((int)i <= info->map_end_index)
	{
		if (!validate_borders(info->split_file[i],
				ft_strlen(info->split_file[i]) - 1, 0))
			return (0);
		i++;
	}
	return (1);
}
