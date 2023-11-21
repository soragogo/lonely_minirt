#include "../includes/minirt.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}


int	draw_frame(void *param)
{
	t_data *img;

	img = (t_data *)param;
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}


void init_minilibx(t_world *world, t_data *img)
{
    int color;

    world->win_w = 500;
    world->win_h = 500;
    world->mlx = mlx_init();
    img->mlx =  world->mlx;
    world->win = mlx_new_window(world->mlx, world->win_w, world->win_h, "miniRT");
    img->win = world->win;
    img->img = mlx_new_image(world->mlx, 500, 500);
    img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length),
								&(img->endian));
    printf("line_length: %d, bites per pic: %d\n", img->line_length, img->bits_per_pixel / 8);
    color = create_rgb(0, 0, 255);
    for (int q = 0; q < 100; q++)
        for (int p = 0; p < 100; p++)
        my_mlx_pixel_put(img, p + world->win_w / 2, -q + world->win_h / 2, color);
	mlx_put_image_to_window(world->mlx, world->win, img->img, 0, 0);
    event_hook(img);

    mlx_loop(world->mlx);
}
