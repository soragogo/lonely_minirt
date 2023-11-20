#include "../includes/minirt.h"
#include "../includes/get_next_line.h"





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

void add_camera(t_world *world, char *line, int count)
{
    char **matrix;
    if (count > 1)
        ft_error("Camera defined more than once");
    matrix = ft_split(line, ' ');
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    printf("Camera: %c\n", *line);
    get_vec_from_str(&(world->camera.coor),matrix[1], 0);
    get_vec_from_str(&(world->camera.vec),matrix[2], 1);
    world->camera.fov = ft_atoi(matrix[3]);
    if (world->camera.fov < 0 || 180 < world->camera.fov)
        ft_error("Camera FOV out of range");
    free_matrix(matrix);
}
void add_light(t_world *world, char *line, int count)
{
    char **matrix;
    double ratio;
    if (count > 1)
        ft_error("Light defined more than once");
    matrix = ft_split(line, ' ');
    // for (int i = 0; matrix[i]; i++)
    //     printf("matrix[%d]: %s\n", i, matrix[i]);
    get_vec_from_str(&(world->light.coor), matrix[1], 0);
    ratio = atod(matrix[2]);
    if (ratio < 0 || 1 < ratio)
        ft_error("Light brightness out of range");
    get_color_from_str(&(world->light.color), matrix[3]);
    world->light.color.r *= atod(matrix[1]) * ratio;
    world->light.color.g *= atod(matrix[1]) * ratio;
    world->light.color.b *= atod(matrix[1]) * ratio;
    free_matrix(matrix);
}

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



void add_element(t_world *world, char *line, int *a_c_l)
{
    if (!ft_strncmp(line, "A ", 2))
    {
        a_c_l[0] += 1;
        add_ambient(world, line, a_c_l[0]);
    }
    else if (!ft_strncmp(line, "C ", 2))
    {
        a_c_l[1] += 1;
        add_camera(world, line, a_c_l[1]);
    }
    else if (!ft_strncmp(line, "L ", 2))
    {
        a_c_l[2] += 1;
        add_light(world, line, a_c_l[2]);
    }
    else if (!ft_strncmp(line, "pl ", 3)
        || !ft_strncmp(line, "sp ", 3)
        || !ft_strncmp(line, "cy ", 3))
        add_object(world, line);
    else
        ft_error("Improper name of element");
}

void add_elements(t_world *world, int fd)
{
    int lines = 0;
    char *line = NULL;
    int a_c_l[3];

    a_c_l[0] = 0;
    a_c_l[1] = 0;
    a_c_l[2] = 0;
    while((line = get_next_line(fd)))
    {
        if (!line[0])
            continue ;
        printf("%d: [%s]\n", lines++, line);
        add_element(world, line, a_c_l);
        free(line);
    }
    if (!(a_c_l[0] * a_c_l[1] * a_c_l[2]))
        ft_error("Essencial element missing in the scene file");
}

int open_scene(const char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        ft_error("No such file or directory");
    return (fd);
}

void create_world_struct(t_world *world)
{
    int fd;

    world->objs = NULL;
    fd = open_scene("/Users/emukamada/Desktop/miniRT/scenes/test.rt");
    add_elements(world, fd);
    close(fd);

}



int main()
{
    t_world world;
    create_world_struct(&world);
    clean_world_struct(&world);
    system("leaks -q miniRT");
    return (0);
}
