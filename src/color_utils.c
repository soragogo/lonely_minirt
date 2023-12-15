#include "../includes/minirt.h"

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int create_rgb_from_fcolor(t_fcolor color)
{
    int r = color.r;
    int g = color.g;
    int b = color.b;
    return (r << 16 | g << 8 | b);
}

t_fcolor color_init(unsigned char r, unsigned char g, unsigned char b)
{
    t_fcolor ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;
    return ret;
}
