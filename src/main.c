#include "../includes/minirt.h"
#include "../includes/get_next_line.h"

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1])
        ft_error("Argument error\nExpected: \"./miniRT [filename]\"");
    t_world world;
    t_data img;

    init_world(&world, av[1]);
    // ft_debug(world);

    init_minilibx(&world, &img);
    draw_image(&world, &img);
    clean_world(&world);
    system("leaks -q miniRT");
    return (0);
}
