#include "../includes/cub3d.h"

int	is_coordinate(char *str)
{
	int	i;
    int counter;

	i = 0;
    counter = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			counter++;
		i++;
	}
	return (counter);
}


int	check_position(t_file *info)
{
	size_t	i;
    int counter;

	i = info->map_start_index;
    counter = 0;
	while ((int)i++ < info->map_end_index)
        counter += is_coordinate(info->split_file[i]);
    if (counter != 1)
        return (0);
    else
	    return (1);
}