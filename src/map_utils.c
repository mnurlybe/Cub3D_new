#include "../includes/cub3d.h"

// copy or dup char ** game->split_file to char ** game->map
int get_map(t_file *file)
{
    char *temp;
    int i;
    // check if map is valid - function placeholder
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
    file->map_w_tiles = ft_strlen(file->map[0]);
    printf("map_h_tiles: %ld\n", file->map_h_tiles);
    printf("map_w_tiles: %ld\n", file->map_w_tiles);
    // print map --> remove this before submitting
    for (int j = 0; file->map[j]; j++)
        printf("{%s}\n", file->map[j]);
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