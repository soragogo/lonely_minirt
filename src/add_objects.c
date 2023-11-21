#include "../includes/minirt.h"


t_elem *find_last_obj(t_world *world)
{
    t_elem *last_obj;

    last_obj = world->objs;
    if (!last_obj)
        return (NULL);
    while(last_obj->next != NULL)
    {
        last_obj = last_obj->next;
    }
    return (last_obj);
}

void create_new_obj(t_elem *new_obj, char **matrix)
{
    int color_idx;

    ft_bzero(new_obj->obj, 3);
    ft_strlcpy(new_obj->obj, matrix[0], 3);
    get_vec_from_str(&(new_obj->coor), matrix[1], 0);
    if (!ft_strncmp(matrix[0], "sp", 2))
    {
        color_idx = 3;
        new_obj->diam = atod(matrix[2]);
    }
    else if (!ft_strncmp(matrix[0], "pl", 2))
    {
        color_idx = 3;
        get_vec_from_str(&(new_obj->vec), matrix[2], 1);
    }
    else
    {
        color_idx = 5;
        get_vec_from_str(&(new_obj->vec), matrix[2], 0);
        new_obj->diam = atod(matrix[3]);
        new_obj->hgt = atod(matrix[3]);
    }
    get_color_from_str(&(new_obj->color), matrix[color_idx]);
}

void create_obj_list(t_world *world, char **matrix)
{
    t_elem *last_obj;
    t_elem *new_obj;

    last_obj = find_last_obj(world);
    new_obj = ft_calloc(sizeof(t_elem), 1);
    if (!new_obj)
        ft_error("Failed to allocate memomry");
    if (last_obj == NULL)
        world->objs = new_obj;
    else
        last_obj->next = new_obj;
    new_obj->next = NULL;
    create_new_obj(new_obj,  matrix);
}

void add_object(t_world *world, char *line)
{
    char **matrix;
    matrix = ft_split(line, ' ');
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    // printf("Object: %c\n", *line);
    create_obj_list(world, matrix);
    free_matrix(matrix);
    return ;
}
