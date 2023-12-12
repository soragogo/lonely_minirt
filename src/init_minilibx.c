#include "../includes/minirt.h"


void init_minilibx(t_world *world, t_data *img)
{
    world->win_w = 500;
    world->win_h = 500;
    world->mlx = mlx_init();
    img->mlx =  world->mlx;
    world->win = mlx_new_window(world->mlx, world->win_w, world->win_h, "miniRT");
    img->win = world->win;
    img->img = mlx_new_image(world->mlx, 500, 500);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length),
								&(img->endian));
    // printf("line_length: %d, bites per pic: %d\n", img->line_length, img->bits_per_pixel / 8);


}
