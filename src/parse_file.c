#include "../includes/cub3d.h"

int    is_newline(char c)
{
    if (c == '\n')
        return (1);
    return (0);
}

/*
 * Prase file and store each line in a char **split_file
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
    line = get_next_line(info->fd);
    temp = ft_strdup(line);
    i = 0;
    while (line)
    {
        if (is_newline(line[0]))
            temp = ft_strjoin(temp, " \n");
        else
            temp = ft_strjoin(temp, line);
        free(line);
        line = get_next_line(info->fd);
        i++;
    }
    info->split_file = ft_split(temp, '\n');
    info->file_size = i;
    close(info->fd);
    free(temp);
    free(line);
    return (info);
}