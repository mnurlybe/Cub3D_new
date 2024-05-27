/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_testing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:44:14 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/05/27 19:45:20 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_textures(t_file *info)
{
	printf("NO: {%s}\n", info->no[0]);
	printf("NO path: {%s}\n", info->no[1]);
	printf("SO: {%s}\n", info->so[0]);
	printf("SO path: {%s}\n", info->so[1]);
	printf("WE: {%s}\n", info->we[0]);
	printf("WE path: {%s}\n", info->we[1]);
	printf("EA: {%s}\n", info->ea[0]);
	printf("EA path: {%s}\n", info->ea[1]);
}

void	print_floor_ceiling(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: {%s}\n", i, arr[i]);
		i++;
	}
}
