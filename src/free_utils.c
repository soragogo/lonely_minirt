#include "../includes/minirt.h"

void free_matrix(char **matrix)
{
    int i = 0;
    while (matrix[i])
        free(matrix[i++]);
    free(matrix);

}

void clean_world_struct(t_world *world)
{
    t_elem *tmp;
    t_elem *node;

    node = world->objs;
    tmp = world->objs;
    while (node)
    {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}
