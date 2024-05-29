/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:30:05 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/29 19:57:38 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * function that checks if the length of the line is lower than the width,
 * then it should add 1s to the end of the line until it reaches the width len
 */
void	add_padding(char **map, size_t width)
{
	int		i;
	size_t	j;
	char	*temp;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < width)
		{
			temp = ft_strdup(map[i]);
			j = ft_strlen(map[i]);
			while (j < width)
			{
				temp = ft_strjoin(temp, "1");
				j++;
			}
			free(map[i]);
			map[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

void	replace_char(char **map, size_t width)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	add_padding(map, width);
}

// copy or dup char ** game->split_file to char ** game->map
int	get_map(t_file *file)
{
	char	*temp;
	int		i;

	temp = ft_strdup("");
	i = file->map_start_index;
	while (i <= file->map_end_index)
	{
		temp = ft_strjoin(temp, file->split_file[i]);
		temp = ft_strjoin(temp, "\n");
		i++;
	}
	file->map = ft_split(temp, '\n');
	file->map_h_tiles = file->map_end_index - file->map_start_index + 1;
	i = file->map_start_index;
	while (i <= file->map_end_index)
	{
		if (ft_strlen(file->split_file[i]) > file->map_w_tiles)
			file->map_w_tiles = ft_strlen(file->split_file[i]);
		i++;
	}
	replace_char(file->map, file->map_w_tiles);
	free(temp);
	return (1);
}

// convert char ** game_data->map to int ** minimap->map
void	copy_map(t_file *game_data, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	minimap->map = malloc(sizeof(int *) * game_data->map_h_tiles);
	if (!minimap->map)
		return ;
	while (game_data->map[i])
	{
		minimap->map[i] = malloc(sizeof(int) * game_data->map_w_tiles);
		if (!minimap->map[i])
			return ;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == '1')
				minimap->map[i][j] = 1;
			else
				minimap->map[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
}
