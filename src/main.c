#include "../includes/minirt.h"
#include "../includes/get_next_line.h"

int main()
{
    t_world world;
    init_world(&world);
    clean_world(&world);
    system("leaks -q miniRT");
    return (0);
}
