#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length \
						+ x * (data->bits_per_pixcel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	t_calc	calc;

	calc.dx = x1 >= x0 ? x1 - x0 : x0 - x1;
	calc.dy = y1 >= y0 ? y0 - y1 : y1 - y0;
	calc.sx = x0 < x1 ? 1 : -1;
	calc.sy = y0 < y1 ? 1 : -1;
	calc.err = calc.dx + calc.dy;
	calc.x = x0;
	calc.y = y0;

	while (1)
	{
		my_mlx_pixel_put(data, calc.x, calc.y, 0x00FF0000);
		if ((calc.x == x1) && (calc.y == y1))
			break ;
		calc.err2 = 2 * calc.err; // 浮動小数点計算を除去して高速化
		if (calc.err2 >= calc.dy)	// step x
		{
			calc.err += calc.dy;
			calc.x += calc.sx;
		}
		if (calc.err2 <= calc.dx) // step y
		{
			calc.err += calc.dx;
			calc.y += calc.sy;
		}
	}
}

void	duplicate_base(t_base **base, t_base **isometric_base, int	map_x_size, int map_y_size)
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
	int pre_y;

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
			convert_isometric_base(&(data->isometric_base[x_i][y_i].x), &(data->isometric_base[x_i][y_i].y), data->isometric_base[x_i][y_i].z);
			data->isometric_base[x_i][y_i].x += WINDOW_WIDTH / 2;
			data->isometric_base[x_i][y_i].y += WINDOW_HEIGHT / 2;
		}
	}
}

void	draw_image(t_data *data)
{
	int		x_i;
	int		y_i;

	duplicate_base(data->base, data->isometric_base, data->map_x_size, data->map_y_size);
	generate_isometric_base(data);

	x_i = -1;
	while (++x_i < data->map_x_size)
	{
		y_i = -1;
		while (++y_i < data->map_y_size)
		{
			if (x_i < data->map_x_size - 1)
				draw_line(data, data->isometric_base[x_i][y_i].x, data->isometric_base[x_i][y_i].y, data->isometric_base[x_i + 1][y_i].x, data->isometric_base[x_i + 1][y_i].y);
			if (y_i < data->map_y_size - 1)
				draw_line(data, data->isometric_base[x_i][y_i].x, data->isometric_base[x_i][y_i].y, data->isometric_base[x_i][y_i + 1].x, data->isometric_base[x_i][y_i + 1].y);
		}
	}
}
