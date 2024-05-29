/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:37:11 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 20:38:00 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info_two(t_file *info)
{
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->map = NULL;
	info->map_start_index = -1;
	info->map_end_index = -1;
	info->map_h_tiles = 0;
	info->map_w_tiles = 0;
	info->textures[NORTH] = NULL;
	info->textures[SOUTH] = NULL;
	info->textures[EAST] = NULL;
	info->textures[WEST] = NULL;
}

t_file	*init_info(t_file *info, char *file)
{
	info = malloc(sizeof(t_file));
	if (!info)
	{
		ft_putstr_fd("Error during memory allocation: file parsing.\n", 2);
		return (NULL);
	}
	info->fd = open(file, O_RDONLY);
	if (info->fd < 0)
	{
		free(info);
		ft_putstr_fd("Error: file is not found.\n", 2);
		return (NULL);
	}
	init_info_two(info);
	return (info);
}

int	is_empty_file(t_file *info, char *line)
{
	if (!line)
	{
		free(line);
		close(info->fd);
		free(info);
		ft_putstr_fd("Error: file is empty.\n", 2);
		return (1);
	}
	return (0);
}

char	*execute_gnl(t_file *info, char *line)
{
	int		i;
	char	*temp;

	temp = ft_strdup(line);
	i = 1;
	while (line)
	{
		free(line);
		line = get_next_line(info->fd);
		if (!line)
		{
			free(line);
			break ;
		}
		if (is_newline(line[0]))
			temp = ft_strjoin(temp, " \n");
		else
			temp = ft_strjoin(temp, line);
		i++;
	}
	info->file_size = i;
	return (temp);
}

/*
 * Parse file and store each line in a char **split_file
 * At this point no checks/error management are done on the file content
 */
t_file	*parse_file(char *file)
{
	t_file	*info;
	char	*temp;
	char	*line;

	info = NULL;
	info = init_info(info, file);
	if (!info)
		return (NULL);
	line = get_next_line(info->fd);
	if (is_empty_file(info, line))
		return (NULL);
	temp = execute_gnl(info, line);
	info->split_file = ft_split(temp, '\n');
	close(info->fd);
	free(temp);
	if (!check_file(info))
	{
		free_textures(info);
		free_array(info->split_file);
		free(info);
		return (NULL);
	}
	get_map(info);
	return (info);
}
