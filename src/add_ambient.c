#include "../includes/minirt.h"

void add_ambient(t_world *world, char *line, int count)
{
    // 実装未完了
    char **matrix;
    if (count > 1)
        ft_error("Ambient defined more than once");
    matrix = ft_split(line, ' ');
    get_color_from_str(&(world->ambient), matrix[2]);
    world->ambient.r *= atod(matrix[1]);
    world->ambient.g *= atod(matrix[1]);
    world->ambient.b *= atod(matrix[1]);
    free_matrix(matrix);
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    world->ambient.r = 0;
}
