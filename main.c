#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include "./minilibx-linux/mlx.h" 
#include "./libft/get_next_line.h"

# define KEY_ESC 65307

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3


typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixcel;
	int		line_length;
	int		endian;
}	t_data;

// TODO: void	my_pixel_put(t_data *data, int x, int y, int color)
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixcel / 8));
	*(unsigned int*)dst = color;
}

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
	if (key == KEY_ESC)
		closer(KEY_ESC, data);
	return (0);
}

int	get_x(char *file)
{
	int	fd;
	char	*line;
	int	lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("error: invalid file name");
	lines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		lines++;
		printf("%s\n", line); //AAAAAAAAAAa
		free(line);
	}
	close(fd);
	return (lines);
}

t_data	file_reader(char *filename)
{
	t_data	data_tmp;
	printf("%d\n", get_x(filename)); //AAAAAAAAAAAAAAAAAAa
	return(data_tmp);
}

int put_circle(int hight, int width, int  x, int y)
{
    int c_x;
    int c_y;
    int radius;

    c_x = width / 2;
    c_y = hight / 2;
    radius = 100;
    //if ((c_x - radius <= x && x <= c_x + radius) && (c_y - radius <= y && y <= c_y + radius))
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
	// data.img_ptr = mlx_new_image(data.mlx, 1920/2, 1080/2);
	// mlx_put_image_to_window(data.mlx, data.win, data->img.img_ptr, 1920/2, 1080/2);
	// data.img->img_ptr = mlx_new_image(data.mlx, 1920, 1080);
	// data.img->addr = mlx_get_data_addr(data.img->img_ptr, &(data.img->bits_per_pixcel), &(data.img->line_length), &(data.img->endian));
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixcel, &data.line_length, &data.endian);
	int i = 0;
	while (i < 1000)
	{
		int j = 0;
		while (j < 1000)
		{
			my_mlx_pixel_put(&data, i, j, put_circle(1000, 1000, i, j));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, key_hook, &data);
	// mlx_hook(data.win, 33, 1L << 17, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}

