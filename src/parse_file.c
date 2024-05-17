#include "../includes/cub3d.h"

int    is_newline(char c)
{
    if (c == '\n')
        return (1);
    return (0);
}

void init_info(t_file *info)
{
    info->no = NULL;
    info->so = NULL;
    info->we = NULL;
    info->ea = NULL;
    info->floor = -1;
    info->ceiling = -1;
    info->map = NULL;
    info->map_start_index = -1;
    info->map_end_index = -1;
    info->map_h_tiles = 0;
    info->map_w_tiles = 0;
}

/*
 * Parse file and store each line in a char **split_file
 * At this point no checks/error management are done on the file content
*/
t_file *parse_file(char *file)
{
    t_file *info;
    char *line;
    char *temp;
    int i;

    info = malloc(sizeof(t_file));
    if (!info)
        return (NULL); // add proper error message
    info->fd = open(file, O_RDONLY);
    if (info->fd < 0)
    {
        free(info);
        return (NULL); // add proper error message
    }
    init_info(info);
    line = get_next_line(info->fd);
    temp = ft_strdup(line);
    i = 1;
    while (line)
    {
        free(line);
        line = get_next_line(info->fd);
        if (!line)
        {
            free(line);
            break;
        }
        if (is_newline(line[0]))
            temp = ft_strjoin(temp, " \n");
        else
            temp = ft_strjoin(temp, line);
        i++;
    }
    info->split_file = ft_split(temp, '\n');
    info->file_size = i;
    close(info->fd);
    free(temp);
    // ADD FULL FILE PARSE AND CHECKS HERE BEFORE COPYINT THE MAP
    check_file(info);
    // print -> to be removed
    // for (size_t i = 0; i < info->file_size; i++)
    // {
    //     // also print address of each line
    //     printf("%s", info->split_file[i]);
    // }
    // copy full map from split_file to map
    get_map(info); 
    return (info);
}