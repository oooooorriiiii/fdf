#include "../includes/fdf.h"

float	calc_default_xy_magnification(int map_x_size, int map_y_size)
{
	int		x_i;
	int		y_i;

	x_i = 1;
	while (x_i * map_x_size < WINDOW_WIDTH)
		x_i++;
	y_i = 1;
	while (y_i * map_y_size < WINDOW_HEIGHT)
		y_i++;
	if (x_i > y_i)
		return (y_i / 1.73);
	else
		return (x_i / 1.73);
}

float	calc_default_z_magnification(t_data *data)
{
	int		max;
	int		x_i;
	int		y_i;
	float	magnification;

	max = 0;
	magnification = 0.05;
	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
			if (max < data->base[x_i][y_i].z)
				max = data->base[x_i][y_i].z;
	}
	if (max != 0)
	{
		while (magnification * max < 50)
			magnification += 0.05;
	}
	return (magnification);
}
