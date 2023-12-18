#include "../includes/minirt.h"

void render_ambient(double *ambient, double *rgb)
{
    int i = 0;
    while (i < 3)
    {
        rgb[i] += ambient[i];
        if (rgb[i] > 1)
            rgb[i] = 1;
        i++;
    }
}
