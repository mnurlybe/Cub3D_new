/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:51:55 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 19:38:28 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	allocate_textures(t_file *info)
{
	info->textures[NORTH] = mlx_load_png(info->no[1]);
	if (!info->textures[NORTH])
		return (0);
	info->textures[SOUTH] = mlx_load_png(info->so[1]);
	if (!info->textures[SOUTH])
		return (0);
	info->textures[EAST] = mlx_load_png(info->ea[1]);
	if (!info->textures[EAST])
		return (0);
	info->textures[WEST] = mlx_load_png(info->we[1]);
	if (!info->textures[WEST])
		return (0);
	return (1);
}
		// mlx_delete_texture(info->textures[NORTH]);

int	check_textures(t_file *info)
{
	if (!info->no || !info->so || !info->we || !info->ea)
		return (0);
	if (array_len(info->no) != 2 || array_len(info->so) != 2
		|| array_len(info->we) != 2 || array_len(info->ea) != 2)
		return (0);
	if (ft_strlen(info->no[0]) != 2 || ft_strlen(info->so[0]) != 2
		|| ft_strlen(info->we[0]) != 2 || ft_strlen(info->ea[0]) != 2)
		return (0);
	if (!allocate_textures(info))
		return (0);
	return (1);
}

int	check_floor_ceiling(char **floor, char **ceiling)
{
	if (!floor && !ceiling)
		return (0);
	if (!floor)
	{
		free_array(ceiling);
		return (0);
	}
	if (!ceiling)
	{
		free_array(floor);
		return (0);
	}
	if (array_len(floor) != 2 || array_len(ceiling) != 2)
	{
		free_array(floor);
		free_array(ceiling);
		return (0);
	}
	if (ft_strlen(floor[0]) != 1 || ft_strlen(ceiling[0]) != 1)
	{
		free_array(floor);
		free_array(ceiling);
		return (0);
	}
	return (1);
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

int	check_file(t_file *info)
{
	if (!get_map_indexes(info))
	{
		ft_putstr_fd("Error: Map is not found.\n", 2);
		return (0);
	}
	if (!parse_textures(info))
	{
		ft_putstr_fd("Error: Textures are not valid.\n", 2);
		return (0);
	}
	if (!parse_floor_ceiling(info))
	{
		ft_putstr_fd("Error: Floor or Ceiling are not valid.\n", 2);
		return (0);
	}
	if (!check_map(info))
	{
		ft_putstr_fd("Error: Map is not valid.\n", 2);
		return (0);
	}
	return (1);
}
