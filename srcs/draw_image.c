#include "../includes/fdf.h"

static void
	generate_isometric_base(t_data *data)
{
	int		x_i;
	int		y_i;

	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
		{
			data->iso_base[x_i][y_i].x *= data->default_magnification[X];
			data->iso_base[x_i][y_i].y *= data->default_magnification[Y];
			data->iso_base[x_i][y_i].z *= data->default_magnification[Z];
			convert_isometric_base(&(data->iso_base[x_i][y_i].x),
				&(data->iso_base[x_i][y_i].y),
				data->iso_base[x_i][y_i].z);
			data->iso_base[x_i][y_i].x += WINDOW_WIDTH / 2;
			data->iso_base[x_i][y_i].y += WINDOW_HEIGHT / 2;
			data->iso_base[x_i][y_i].color = data->base[x_i][y_i].color;
		}
	}
}

void	draw_image(t_data *data)
{
	int		x_i;
	int		y_i;

	duplicate_base(data->base, data->iso_base,
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
