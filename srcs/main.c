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
	return (0);
}

int	main(int args, char **argv)
{
	t_data	data;
	long	cpu_time;

	printf("%d, %d", X, Y);
	cpu_time = clock();
	(void)args;
	data = file_reader(argv[1]);
	printf("time: %f\n", (double)cpu_time / CLOCKS_PER_SEC);
	puts("Finish file read");
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixcel, &data.line_length, &data.endian);
	draw_image(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, key_hook, &data);
	// TODO: mlx_hook(data.win, 33, 1L << 17, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}

