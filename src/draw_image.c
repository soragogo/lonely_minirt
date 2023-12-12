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

void get_next_position(t_vec *pos, char *param, t_vec scr_x, t_vec scr_y)
{
    if (!ft_strncmp(param, "x", 1))
    {
        pos->x = pos->x + scr_x.x;
        pos->y = pos->y + scr_x.y;
        pos->z = pos->z + scr_x.z;
    }
    else
    {
        pos->x = pos->x - scr_y.x;
        pos->y = pos->y - scr_y.y;
        pos->z = pos->z - scr_y.z;
    }
}


void draw_image(t_world *world, t_data *img)
{
    t_vec scr_x;
    t_vec scr_y;
    t_vec pos;
    t_vec dir_vec;
    t_vec sphere2camera;

    scr_x = world->camera.scr_x;
    scr_y = world->camera.scr_y;
    pos = world->camera.scr_pos;
    printf("objs: %s\n", world->objs->obj);
    sphere2camera = vec_sub(world->camera.coor, world->objs->coor);
    int color;
    int index = 0;
    for (int y = -250; y < 250; y++)
    {
        for (int x = -250; x < 250; x++)
        {
            index++;
            dir_vec = vec_normalize(vec_sub(pos, world->camera.coor));
            double a = vec_dot(dir_vec, dir_vec);
            double b = 2 * vec_dot(sphere2camera, dir_vec);
            double c = vec_dot(sphere2camera, sphere2camera) - world->objs->diam * world->objs->diam;
            double d = b * b - 4 * a * c;
            if( d >= 0)
            {
                printf("[%d] a: %f, b: %f, c: %f, d: %f",index, a,b,c,d);
                printf(" x: %d, y: %d\n",x, y);
            }
            if (d >= 0)
                color = create_rgb(255, 0, 0);
            else
                color = create_rgb(0, 0, 0);
            my_mlx_pixel_put(img, x + world->win_w / 2, -y + world->win_h / 2, color);
            get_next_position(&pos, "x", scr_x, scr_y);
        }
            get_next_position(&pos, "y", scr_x, scr_y);
    }
	mlx_put_image_to_window(world->mlx, world->win, img->img, 0, 0);

    event_hook(img);

    mlx_loop(world->mlx);
}
