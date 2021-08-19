#include "../includes/fdf.h"

int	closer(int keycode, t_data *data)
{
	(void)keycode;
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	key_hook(int key, void *v)
{
	t_data	*data;

	data = (t_data *)v;
	draw_image(data);
	if (key == KEY_ESC)
		closer(KEY_ESC, data);
	return (0);
}



int put_circle(int hight, int width, int  x, int y)
{
    int c_x;
    int c_y;
    int radius;

    c_x = width / 2;
    c_y = hight / 2;
    radius = 100;
    if ((x - c_x) * (x -c_x) + (y - c_y) * (y - c_y) <= radius * radius)
        return (0x00FF0000);
    return (0);
}

int	main(int args, char **argv)
{
	t_data	data;

	(void)args;
	data = file_reader(argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "fdf");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	puts("*********:main");
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixcel, &data.line_length, &data.endian);
	// int i = 0;
	// while (i < 1000)
	// {
	// 	int j = 0;
	// 	while (j < 1000)
	// 	{
	// 		my_mlx_pixel_put(&data, i, j, put_circle(1000, 1000, i, j));
	// 		j++;
	// 	}
	// 	i++;
	// }
	// int i = -1;
	// while (++i < 1000)
	// {
	// 	my_mlx_pixel_put(&data, i, i, 0x00FF0000);
	// }
	draw_image(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, key_hook, &data);
	// TODO: mlx_hook(data.win, 33, 1L << 17, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}

