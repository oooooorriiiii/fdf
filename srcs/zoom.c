#include "../includes/fdf.h"

float	calc_default_xy_magnification(int map_x_size, int map_y_size)
{
	int		x_i;
	int		y_i;

	x_i = 1;
	while (x_i * map_x_size < WIN_W)
		x_i++;
	y_i = 1;
	while (y_i * map_y_size < WIN_H)
		y_i++;
	if (x_i > y_i)
		return (y_i / 1.73);
	else
		return (x_i / 1.73);
}

static float
	return_z_mag(int max, int min, float magnification, float magnification_neg)
{
	if (max != 0)
	{
		while (magnification * max < 50)
			magnification += 0.05;
	}
	if (min != 0)
	{
		while (magnification_neg * -min < 50)
			magnification_neg += 0.05;
	}
	if (magnification > magnification_neg)
		return (magnification);
	else
		return (magnification_neg);
}

float	calc_default_z_magnification(t_data *data)
{
	int		max;
	int		min;
	int		i[2];
	float	magnification;
	float	magnification_neg;

	max = 0;
	min = 0;
	magnification = 0.05;
	magnification_neg = 0.05;
	i[X] = -1;
	while (++i[X] < data->map_x_size)
	{
		i[Y] = -1;
		while (++i[Y] < data->map_y_size)
		{
			if (max < data->base[i[X]][i[Y]].z)
				max = data->base[i[X]][i[Y]].z;
			if (min >data->base[i[X]][i[Y]].z)
				min = data->base[i[X]][i[Y]].z;
		}
	}
	return (return_z_mag(max, min, magnification, magnification_neg));
}

void	zoom(int key, t_data *data)
{
	int	magnification_xy;

	magnification_xy = calc_default_xy_magnification(data->map_x_size,
			data->map_y_size);
	if (key == KEY_PLUS)
		data->camera->zoom += magnification_xy;
	else if (key == KEY_MINUS)
	{
		if (data->camera->zoom >= magnification_xy)
			data->camera->zoom -= magnification_xy;
	}
	ft_bzero(data->addr,
		WIN_W * WIN_H * (data->bits_per_pixcel / 8));
	draw_image(data);
}
