/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:48:26 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 15:41:30 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_textures(t_file *info)
{
	int	i;

	i = 0;
	while (i < info->map_start_index)
	{
		if (ft_strnstr(info->split_file[i], "NO",
				ft_strlen(info->split_file[i])) != NULL)
			info->no = ft_split(info->split_file[i], ' ');
		else if (ft_strnstr(info->split_file[i], "SO",
				ft_strlen(info->split_file[i])) != NULL)
			info->so = ft_split(info->split_file[i], ' ');
		else if (ft_strnstr(info->split_file[i], "WE",
				ft_strlen(info->split_file[i])) != NULL)
			info->we = ft_split(info->split_file[i], ' ');
		else if (ft_strnstr(info->split_file[i], "EA",
				ft_strlen(info->split_file[i])) != NULL)
			info->ea = ft_split(info->split_file[i], ' ');
		i++;
	}
	if (!check_textures(info))
		return (0);
	return (1);
}

int	parse_rgb(char *floor, char *ceiling, t_file *info)
{
	char	**floor_rgb;
	char	**ceiling_rgb;
	int		i;

	floor_rgb = ft_split(floor, ',');
	ceiling_rgb = ft_split(ceiling, ',');
	if (array_len(floor_rgb) != 3 || array_len(ceiling_rgb) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_num(floor_rgb[i]) || !is_num(ceiling_rgb[i]))
			return (0);
		if (ft_atoi(floor_rgb[i]) < 0 || ft_atoi(floor_rgb[i]) > 255
			|| ft_atoi(ceiling_rgb[i]) < 0 || ft_atoi(ceiling_rgb[i]) > 255)
			return (0);
		info->floor[i] = ft_atoi(floor_rgb[i]);
		info->ceiling[i] = ft_atoi(ceiling_rgb[i]);
		i++;
	}
	free_array(floor_rgb);
	free_array(ceiling_rgb);
	return (1);
}

int	parse_floor_ceiling_two(char **floor, char **ceiling, t_file *info)
{
	if (!check_floor_ceiling(floor, ceiling))
		return (0);
	if (!parse_rgb(floor[1], ceiling[1], info))
	{
		free_array(floor);
		free_array(ceiling);
		return (0);
	}
	free_array(floor);
	free_array(ceiling);
	return (1);
}

int	parse_floor_ceiling(t_file *info)
{
	int		i;
	char	**floor;
	char	**ceiling;

	floor = NULL;
	ceiling = NULL;
	i = 0;
	while (i < info->map_start_index)
	{
		if (ft_strnstr(info->split_file[i], "F",
				ft_strlen(info->split_file[i])) != NULL)
			floor = ft_split(info->split_file[i], ' ');
		else if (ft_strnstr(info->split_file[i], "C",
				ft_strlen(info->split_file[i])) != NULL)
			ceiling = ft_split(info->split_file[i], ' ');
		i++;
	}
	if (!parse_floor_ceiling_two(floor, ceiling, info))
		return (0);
	return (1);
}

int	validate_borders(char *line, size_t end_index, size_t start_index)
{
	while (line[start_index])
	{
		if (line[start_index] == ' ')
		{
			start_index++;
			continue ;
		}
		if (line[start_index] != '1')
			return (0);
		if (line[start_index] == '1')
			break ;
	}
	while (line[end_index])
	{
		if (line[end_index] == ' ')
		{
			end_index--;
			continue ;
		}
		if (line[end_index] != '1')
			return (0);
		if (line[end_index] == '1')
			break ;
	}
	return (1);
}
