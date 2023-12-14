#include "../includes/minirt.h"



void init_world(t_world *world, char *filename)
{
    int fd;

    world->objs = NULL;
    fd = open_scene(filename);
    add_elements(world, fd);
    close(fd);
}
