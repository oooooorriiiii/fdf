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
	float	default_magnigication[3];

	default_magnigication[X] = calc_default_xy_magnification(data->map_x_size,
			data->map_y_size);
	default_magnigication[Y] = default_magnigication[X];
	default_magnigication[Z] = calc_default_z_magnification(data);
	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
		{
			data->isometric_base[x_i][y_i].x *= default_magnigication[X];
			data->isometric_base[x_i][y_i].y *= default_magnigication[Y];
			data->isometric_base[x_i][y_i].z *= default_magnigication[Z];
			convert_isometric_base(&(data->isometric_base[x_i][y_i].x),
				&(data->isometric_base[x_i][y_i].y),
				data->isometric_base[x_i][y_i].z);
			rotate_x(&(data->isometric_base[x_i][y_i].y),
				&(data->isometric_base[x_i][y_i].z), data->camera->theta_x);
			data->isometric_base[x_i][y_i].x += WINDOW_WIDTH / 2;
			data->isometric_base[x_i][y_i].y += WINDOW_HEIGHT / 2;
			data->isometric_base[x_i][y_i].color = data->base[x_i][y_i].color;
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
				draw_line(data, x_i, y_i, X_LINE);
			if (y_i < data->map_y_size - 1)
				draw_line(data, x_i, y_i, Y_LINE);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
