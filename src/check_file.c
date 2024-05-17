#include "../includes/cub3d.h"
/**
 * this function will consist of several functions. 
 * step one is to check if NO, SO, WE, and EA are correct and assign it to the t_file struct.
 * step two is to check if the floor and ceiling are correct and assign it to the t_file struct.
 * step three is to check if the map is correct and assign it to the t_file struct.
 * Function return 1 if the file is correct and 0 if the file is incorrect.
*/
int is_only_whitespace(char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int is_only_ones(char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int get_map_indexes(t_file *info)
{
    size_t i;
    i = 0;
    while (i < info->file_size)
    {
        if (!is_only_whitespace(info->split_file[i]) && is_only_ones(info->split_file[i]))
        {
            info->map_start_index = i;
            break;
        }
        i++;
    }
    i++;
    while (i < info->file_size)
    {
        if ((!is_only_whitespace(info->split_file[i]) && is_only_ones(info->split_file[i])))
        {
            info->map_end_index = i;
            break;
        }
        i++;
    }
    if (info->map_start_index == -1 || info->map_end_index == -1)
        return (0);
    return (1);
}

int check_file(t_file *info)
{
    if (!get_map_indexes(info))
    {
        return (1); // add proper error messagme - start and end index of map not found
    }
    printf("map start index: %d\n", info->map_start_index);
    printf("map end index: %d\n", info->map_end_index);
    // check if NO, SO, WE, and EA are correct and assign it to the t_file struct.
    // check if the floor and ceiling are correct and assign it to the t_file struct.
    // check if the map is correct and assign it to the t_file struct.
    return (0);
}