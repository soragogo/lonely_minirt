#include "../includes/minirt.h"

void render_ambient(double *ambient, t_fcolor *color)
{
    color->r = (unsigned char)((double)color->r * ambient[0]);
    color->g = (unsigned char)((double)color->g * ambient[1]);
    color->b = (unsigned char)((double)color->b * ambient[2]);
}
