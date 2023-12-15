#include "../includes/minirt.h"
#include "../includes/get_next_line.h"

void check_arg_error(int ac, char **av)
{
    int i = 0;
    if (ac != 2 || !*av[1])
        ft_error("Argument error\nExpected: \"./miniRT [filename]\"");
    i = ft_strlen(av[1]);
    if (i > 3)
    {
        i -= 3;
        if (!ft_strncmp(&av[1][i], ".rt", 4))
            return ;
    }
    ft_error("Expected: [(filename).rt]");
}

int main(int ac, char **av)
{
    check_arg_error(ac, av);

    t_world world;
    t_data img;

    init_world(&world, av[1]);
    // ft_debug(world);

    printf("[1] %f, %f, %f\n", world.ambient[0], world.ambient[1], world.ambient[2]);
    init_minilibx(&world, &img);
    printf("[2] %f, %f, %f\n", world.ambient[0], world.ambient[1], world.ambient[2]);
    draw_image(&world, &img);
    clean_world(&world);
    system("leaks -q miniRT");
    return (0);
}
