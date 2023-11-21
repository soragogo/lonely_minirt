#include "../includes/minirt.h"



void init_world(t_world *world)
{
    int fd;

    world->objs = NULL;
    fd = open_scene("/Users/emukamada/Desktop/miniRT/scenes/test.rt");
    add_elements(world, fd);
    close(fd);
}
