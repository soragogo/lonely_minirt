#include "../includes/minirt.h"
int	exit_program(int keycode, t_data *img)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(img->mlx, img->win);
        mlx_destroy_image(img->mlx, img->img);
		exit(0);
		return (0);
	}
	return (0);
}

int	close_program(void *param)
{
	(void)param;
	exit(0);
	return (0);
}



void event_hook(t_data *img)
{
    mlx_key_hook(img->win, exit_program, img);
	mlx_hook(img->win, 17, 0, &close_program, NULL);


}
