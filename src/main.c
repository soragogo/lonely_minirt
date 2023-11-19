#include "../includes/minirt.h"
#include "../includes/get_next_line.h"

void add_ambient(t_world *world, char *line, int count)
{
    if (count > 1)
        ft_error("Ambient defined more than once");
    printf("Ambient: %c\n", *line);
    world->ambient.r = 0;
}
void add_camera(t_world *world, char *line, int count)
{
    if (count > 1)
        ft_error("Camera defined more than once");
    printf("Camera: %c\n", *line);
    world->ambient.r = 0;
}
void add_light(t_world *world, char *line, int count)
{
    if (count > 1)
        ft_error("Light defined more than once");
    printf("Light: %c\n", *line);
    world->ambient.r = 0;
}
void add_object(t_world *world, char *line)
{
    printf("Object: %c\n", *line);
    world->ambient.r = 0;
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

    fd = open_scene("/Users/emukamada/Desktop/miniRT/scenes/test.rt");
    add_elements(world, fd);
    close(fd);

}

int main()
{
    t_world world;
    create_world_struct(&world);
    system("leaks -q miniRT");
    return (0);
}
