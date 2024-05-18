#include "../includes/cub3d.h"

/**
 * function that checks if the length of the line is lower than the width, 
 * then it should add 1s to the end of the line until it reaches the width len
*/
void    add_padding(char **map, size_t width)
{
    int i;
    size_t j;
    char *temp;

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

void replace_char(char **map, size_t width)
{
    int i;
    int j;

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
int get_map(t_file *file)
{
    char *temp;
    int i;
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
    // file->map_w_tiles = ft_strlen(file->map[0]);
    // printf("map_h_tiles: %ld\n", file->map_h_tiles);
    // printf("map_w_tiles: %ld\n", file->map_w_tiles);
    replace_char(file->map, file->map_w_tiles);
    // print map --> remove this before submitting
    // for (int j = 0; file->map[j]; j++)
    //     printf("{%s}\n", file->map[j]);
    free(temp);
    return (1);
}

// convert char ** game_data->map to int ** minimap->map
void    copy_map(t_file *game_data, t_minimap *minimap)
{
    int i = 0;
    int j = 0;
    minimap->map = malloc(sizeof(int *) * game_data->map_h_tiles);
    if (!minimap->map)
        return ; // add proper error message
    while (game_data->map[i])
    {
        minimap->map[i] = malloc(sizeof(int) * game_data->map_w_tiles);
        if (!minimap->map[i])
            return ; // add proper error message
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