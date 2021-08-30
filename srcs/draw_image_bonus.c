#include "../includes/fdf.h"

static void
	generate_isometric_base_bonus(t_data *data)
{
	int	i[2];

	i[X] = -1;
	while (++i[X] < data->map_x_size)
	{
		i[Y] = -1;
		while (++i[Y] < data->map_y_size)
		{
			data->iso_base[i[X]][i[Y]].x *= data->camera->zoom;
			data->iso_base[i[X]][i[Y]].y *= data->camera->zoom;
			data->iso_base[i[X]][i[Y]].z *= data->camera->zoom;
			convert_isometric_base(&(data->iso_base[i[X]][i[Y]].x),
				&(data->iso_base[i[X]][i[Y]].y),
				data->iso_base[i[X]][i[Y]].z);
			rotate_x(&(data->iso_base[i[X]][i[Y]].y),
				&(data->iso_base[i[X]][i[Y]].z), data->camera->theta_x);
			rotate_y(&(data->iso_base[i[X]][i[Y]].x),
				&(data->iso_base[i[X]][i[Y]].z), data->camera->theta_y);
			rotate_z(&(data->iso_base[i[X]][i[Y]].x),
				&(data->iso_base[i[X]][i[Y]].y), data->camera->theta_z);
			data->iso_base[i[X]][i[Y]].x += WINDOW_WIDTH / 2;
			data->iso_base[i[X]][i[Y]].y += WINDOW_HEIGHT / 2;
			data->iso_base[i[X]][i[Y]].color = data->base[i[X]][i[Y]].color;
		}
	}
}

void	draw_image(t_data *data)
{
	int		x_i;
	int		y_i;

	duplicate_base(data->base, data->iso_base,
		data->map_x_size, data->map_y_size);
	generate_isometric_base_bonus(data);
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
