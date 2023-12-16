#include "../includes/minirt.h"

void add_light(t_world *world, char *line, int count)
{
    char **matrix;
    double ratio;
    t_fcolor tmp;
    // printf("[8] %f, %f, %f\n", world->ambient[0], world->ambient[1], world->ambient[2]);
    if (count > 1)
        ft_error("Light defined more than once");
    // ft_strlcpy(world->light.obj, "L\0\0", 3);
    matrix = ft_split(line, ' ');
        if (!matrix[1] || !matrix[2] || !matrix[3])
        ft_error("Light does not have enough number of elements");
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    get_vec_from_str(&(world->light.coor), matrix[1], 0);
    ratio = atod(matrix[2]);
    if (ratio < 0 || 1 < ratio)
        ft_error("Light brightness out of range");
    get_color_from_str(&tmp, matrix[3]);
    world->light.rgb[0] = ((double)tmp.r / 255) * ratio;
    world->light.rgb[1] = ((double)tmp.g / 255) * ratio;
    world->light.rgb[2] = ((double)tmp.b / 255) * ratio;
    free_matrix(matrix);
    // printf("[9] %f, %f, %f\n", world->ambient[0], world->ambient[1], world->ambient[2]);
}
