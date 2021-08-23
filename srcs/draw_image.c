#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixcel / 8));
	*(unsigned int *)dst = color;
}

void	duplicate_base(t_base **base, t_base **isometric_base,
						int	map_x_size, int map_y_size)
{
	int		x_i;
	int		y_i;

	x_i = -1;
	while (++x_i < map_x_size)
	{
		y_i = -1;
		while (++y_i < map_y_size)
			isometric_base[x_i][y_i] = base[x_i][y_i];
	}
}

void	convert_isometric_base(float *x, float *y, int z)
{
	int	pre_x;
	int	pre_y;

	pre_x = (int)*x;
	pre_y = (int)*y;
	*x = (pre_x - pre_y) * cos(0.523599);
	*y = -z + (pre_x + pre_y) * sin(0.523599);
}

void	generate_isometric_base(t_data *data)
{
	int		x_i;
	int		y_i;

	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
		{
			data->isometric_base[x_i][y_i].x *= data->camera->zoom / 2;
			data->isometric_base[x_i][y_i].y *= data->camera->zoom / 2;
			data->isometric_base[x_i][y_i].z *= data->camera->zoom / 16;
			convert_isometric_base(&(data->isometric_base[x_i][y_i].x),
				&(data->isometric_base[x_i][y_i].y),
				data->isometric_base[x_i][y_i].z);
			data->isometric_base[x_i][y_i].x += WINDOW_WIDTH / 2;
			data->isometric_base[x_i][y_i].y += WINDOW_HEIGHT / 2;
		}
	}
}

void	draw_image(t_data *data)
{
	int		x_i;
	int		y_i;

	duplicate_base(data->base, data->isometric_base,
		data->map_x_size, data->map_y_size);
	generate_isometric_base(data);
	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
		{
			if (x_i < data->map_x_size - 1)
				draw_line(data, data->isometric_base[x_i][y_i].x,
					data->isometric_base[x_i][y_i].y,
					data->isometric_base[x_i + 1][y_i].x,
					data->isometric_base[x_i + 1][y_i].y);
			if (y_i < data->map_y_size - 1)
				draw_line(data, data->isometric_base[x_i][y_i].x,
					data->isometric_base[x_i][y_i].y,
					data->isometric_base[x_i][y_i + 1].x,
					data->isometric_base[x_i][y_i + 1].y);
		}
	}
}
