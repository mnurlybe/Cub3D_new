#include "../includes/cub3d.h"
/**
 * this function will consist of several functions. 
 * step one is to check if NO, SO, WE, and EA are correct and assign it to the t_file struct.
 * step two is to check if the floor and ceiling are correct and assign it to the t_file struct.
 * step three is to check if the map is correct and assign it to the t_file struct.
 * Function return 1 if the file is correct and 0 if the file is incorrect.
*/

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
    // printf("map start index: %d\n", info->map_start_index); // for debugging, to be removed
    // printf("map end index: %d\n", info->map_end_index); // for debugging, to be removed
    return (1);
}

int check_textures(t_file *info)
{
    if (!info->no || !info->so || !info->we || !info->ea) // if some textures are missing
        return (0);
    if (array_len(info->no) != 2 || array_len(info->so) != 2 
        || array_len(info->we) != 2 || array_len(info->ea) != 2) // if there are more than 2 elem in the textures
        return (0);
    if (ft_strlen(info->no[0]) != 2 || ft_strlen(info->so[0]) != 2 || ft_strlen(info->we[0]) != 2 || ft_strlen(info->ea[0]) != 2)
        return (0);
    //ADD HERE a check if the path to the texture file is correct
    return (1);
}

int parse_textures(t_file *info)
{
    int i;
    i = 0;
    while (i < info->map_start_index)
    {
        if (ft_strnstr(info->split_file[i], "NO", ft_strlen(info->split_file[i])) != NULL)
            info->no = ft_split(info->split_file[i], ' ');
        else if (ft_strnstr(info->split_file[i], "SO", ft_strlen(info->split_file[i])) != NULL)
            info->so = ft_split(info->split_file[i], ' ');
        else if (ft_strnstr(info->split_file[i], "WE", ft_strlen(info->split_file[i])) != NULL)
            info->we = ft_split(info->split_file[i], ' ');
        else if (ft_strnstr(info->split_file[i], "EA", ft_strlen(info->split_file[i])) != NULL)
            info->ea = ft_split(info->split_file[i], ' ');
        i++;
    }
    // print_textures(info); // for debugging, to be removed
    if (!check_textures(info))
        return (0);
    return (1);
}

int check_floor_ceiling(char **floor, char **ceiling)
{
    if (!floor || !ceiling) // if some textures are missing
        return (0);
    if (array_len(floor) != 2 || array_len(ceiling) != 2) // if there are more than 2 elem in the textures
        return (0);
    if (ft_strlen(floor[0]) != 1 || ft_strlen(ceiling[0]) != 1)
        return (0);
    return (1);
}

int parse_rgb(char *floor, char *ceiling, t_file *info)
{
    char **floor_rgb;
    char **ceiling_rgb;
    int i;
    floor_rgb = ft_split(floor, ',');
    ceiling_rgb = ft_split(ceiling, ',');
    // check if the arrays are of length 3
    if (array_len(floor_rgb) != 3 || array_len(ceiling_rgb) != 3)
        return (0);
    // check if the values are between 0 and 255, check if the values are digits, assign the values to the t_file struct
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

int parse_floor_ceiling(t_file *info)
{
    int i;
    char **floor;
    char **ceiling;

    i = 0;
    while (i < info->map_start_index)
    {
        if (ft_strnstr(info->split_file[i], "F", ft_strlen(info->split_file[i])) != NULL)
            floor = ft_split(info->split_file[i], ' ');
        else if (ft_strnstr(info->split_file[i], "C", ft_strlen(info->split_file[i])) != NULL)
            ceiling = ft_split(info->split_file[i], ' ');
        i++;
    }
    // print_floor_ceiling(floor); // for debugging, to be removed
    // print_floor_ceiling(ceiling); // for debugging, to be removed
    if (!check_floor_ceiling(floor, ceiling) || !parse_rgb(floor[1], ceiling[1], info))
    {
        free_array(floor);
        free_array(ceiling);
        return (0);
    }
    free_array(floor);
    free_array(ceiling);
    return (1);
}

int check_map(t_file *info)
{
    size_t i;
    i = info->map_start_index;
    // check if there are any empty lines in the map and if there are any characters other than 0, 1, N, S, E, W and space
    while ((int)i < info->map_end_index)
    {
        if (is_only_whitespace(info->split_file[i]) || !is_only_allowed_chars(info->split_file[i]))
            return (0);
        i++;
    }
    i++;
    // check if the map is the last element in the file
    while (i < info->file_size)
    {
        if (!is_only_whitespace(info->split_file[i]))
            return (0);
        i++;
    }
    return (1);
}

int check_file(t_file *info)
{
    if (!get_map_indexes(info))
    {
        printf("map not found\n");
        return (1); // add proper error messagme - start and end index of map not found
    }
    // check if NO, SO, WE, and EA are correct and assign it to the t_file struct.
    if (!parse_textures(info))
    {
        printf("textures: error\n");
        return (1); // add proper error message - textures not found
    }
    // check if the floor and ceiling are correct and assign it to the t_file struct.
    if (!parse_floor_ceiling(info))
    {
        printf("floor and ceiling: error\n");
        return (1); // add proper error message - floor and ceiling not found
    }
    // check if the map is correct and assign it to the t_file struct.
    if (!check_map(info))
    {
        printf("map: error\n");
        return (1); // add proper error message - map not found
    }
    return (0);
}
