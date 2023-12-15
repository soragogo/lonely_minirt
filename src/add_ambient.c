#include "../includes/minirt.h"

void add_ambient(t_world *world, char *line, int count)
{
    // 実装未完了

    t_fcolor tmp;
    double ratio;
    char **matrix;
    if (count > 1)
        ft_error("Ambient defined more than once");
    matrix = ft_split(line, ' ');
    if (!matrix[1] || !matrix[2])
        ft_error("Ambient does not have enough number of elements");
    get_color_from_str(&(tmp), matrix[2]);
    ratio = atod(matrix[1]);
    if (ratio < 0 || 1 < ratio)
        ft_error("Ambient out of range");
    world->ambient[0] = ((double)tmp.r / 255) * ratio;
    world->ambient[1] = ((double)tmp.g / 255) * ratio;
    world->ambient[2] = ((double)tmp.b / 255) * ratio;
    printf("%f, %f, %f\n", world->ambient[0], world->ambient[1], world->ambient[2]);
    free_matrix(matrix);
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
}
