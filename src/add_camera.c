#include "../includes/minirt.h"

void add_camera(t_world *world, char *line, int count)
{
    char **matrix;
    if (count > 1)
        ft_error("Camera defined more than once");
    matrix = ft_split(line, ' ');
    if (!matrix[1] || !matrix[2] || !matrix[3])
        ft_error("Camera does not have enough number of elements");
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    // printf("Camera: %c\n", *line);
    get_vec_from_str(&(world->camera.coor),matrix[1], 0);
    get_vec_from_str(&(world->camera.vec),matrix[2], 1);
    if (vec_mag(world->camera.vec) != 1)
        ft_error("The size of the camera vector should be 1");
    world->camera.fov = ft_atoi(matrix[3]);
    if (world->camera.fov < 0 || 180 < world->camera.fov)
        ft_error("Camera FOV out of range");
    get_screen_start_position(world);
    free_matrix(matrix);
}

