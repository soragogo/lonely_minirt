#include "../includes/minirt.h"

void render_ambient(double *ambient, t_fcolor *color)
{
    // printf("r: %d, g: %d, b: %d\n", color->r, color->g, color->b);
    color->r = (unsigned char)((double)color->r * ambient[0]);
    color->g = (unsigned char)((double)color->g * ambient[1]);
    color->b = (unsigned char)((double)color->b * ambient[2]);
    // printf("★r: %f, g: %f, b: %f\n", ambient[0], ambient[1], ambient[2]);
    // printf("★r: %d, g: %d, b: %d\n", color->r, color->g, color->b);
}
