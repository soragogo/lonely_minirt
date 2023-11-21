#include "../includes/minirt.h"
#include "../includes/get_next_line.h"

int main()
{
    t_world world;
    t_data img;

    init_world(&world);
    // ft_debug(world);
    init_minilibx(&world, &img);
    clean_world(&world);
    system("leaks -q miniRT");
    return (0);
}
