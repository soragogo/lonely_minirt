#include "../includes/minirt.h"

void add_ambient(t_world *world, char *line, int count)
{
    // 実装未完了
    double ratio;
    char **matrix;
    if (count > 1)
        ft_error("Ambient defined more than once");
    matrix = ft_split(line, ' ');
    if (!matrix[1] || !matrix[2])
        ft_error("Ambient does not have enough number of elements");
    get_color_from_str(&(world->ambient), matrix[2]);
    ratio = atod(matrix[1]);
    if (ratio < 0 || 1 < ratio)
        ft_error("Ambient out of range");
    world->ambient.r *= ratio;
    world->ambient.g *= ratio;
    world->ambient.b *= ratio;
    free_matrix(matrix);
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
}
