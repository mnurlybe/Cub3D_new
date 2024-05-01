#include "../includes/cub3d.h"

/**
 * before this function there will be an error management function 
 * to check if the map is valid, 
 * but now to keep it simple I pass only valid maps.
 * */ 
// copy or dup char ** game->split_file to char ** game->map
void get_map(t_file *file)
{
    char *temp;
    int i;
    // check if map is valid - function placeholder
    temp = ft_strdup("");
    i = 0;
    while (file->split_file[i])
    {
        temp = ft_strjoin(temp, file->split_file[i]);
        temp = ft_strjoin(temp, "\n");
        i++;
    }
    file->map = ft_split(temp, '\n');
    file->map_h_tiles = i;
    file->map_w_tiles = ft_strlen(file->map[0]);
    // print map --> remove this before submitting
    // for (int i = 0; file->map[i]; i++)
    //     printf("%s\n", file->map[i]);
    free(temp);
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