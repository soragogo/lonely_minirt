#include "../includes/minirt.h"

void add_light(t_world *world, char *line, int count)
{
    char **matrix;
    double ratio;
    if (count > 1)
        ft_error("Light defined more than once");
    ft_strlcpy(world->light.obj, "L\0\0", 3);
    matrix = ft_split(line, ' ');
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    get_vec_from_str(&(world->light.coor), matrix[1], 0);
    ratio = atod(matrix[2]);
    if (ratio < 0 || 1 < ratio)
        ft_error("Light brightness out of range");
    get_color_from_str(&(world->light.color), matrix[3]);
    world->light.color.r *= ratio;
    world->light.color.g *= ratio;
    world->light.color.b *= ratio;
    free_matrix(matrix);
}
