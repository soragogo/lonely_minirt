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

int create_rgb_from_fcolor(t_fcolor color)
{
    int r = color.r;
    int g = color.g;
    int b = color.b;
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
        pos->x = pos->x - scr_x.x * 500;
        pos->y = pos->y - scr_x.y * 500;
        pos->z = pos->z - scr_x.z * 500;
        pos->x = pos->x - scr_y.x;
        pos->y = pos->y - scr_y.y;
        pos->z = pos->z - scr_y.z;
    }
}


void draw_image(t_world *world, t_data *img)
{
    t_vec scr_x;
    t_vec scr_y;
    t_vec* pos;

    scr_x = world->camera.scr_x;
    scr_y = world->camera.scr_y;
    pos = &(world->camera.scr_pos);
    int color;
    ft_debug(*world);
    for (int y = -250; y < 250; y++)
    {
        for (int x = -250; x < 250; x++)
        {
            color = render_objects(world);
            my_mlx_pixel_put(img, x + world->win_w / 2, -y + world->win_h / 2, color);
            get_next_position(pos, "x", scr_x, scr_y);
        }
            // puts("\n一行完了　\n");
            get_next_position(pos, "y", scr_x, scr_y);
    }
	mlx_put_image_to_window(world->mlx, world->win, img->img, 0, 0);

    event_hook(img);
    mlx_loop(world->mlx);
}
