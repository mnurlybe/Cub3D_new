#include "../includes/cub3d.h"

void print_textures(t_file *info)
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

void print_floor_ceiling(char **arr)
{
    for (int i = 0; arr[i]; i++)
        printf("arr[%d]: {%s}\n", i, arr[i]);
}