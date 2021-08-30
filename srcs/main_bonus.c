#include "../includes/fdf.h"
#include <time.h>

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
	else if (key == KEY_ARROW_UP || key == KEY_ARROW_DOWN
		|| key == KEY_ARROW_RIGHT || key == KEY_ARROW_LEFT
		|| key == KEY_8 || key == KEY_9)
		rotate(key, data);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		zoom(key, data);
	else if (key == KEY_M)
		draw_image_military(data);
	return (0);
}

int	main(int args, char **argv)
{
	t_data	data;

	(void)args;
	data = file_reader(argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixcel,
			&data.line_length, &data.endian);
	draw_image(&data);
	mlx_hook(data.win, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}