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

void	duplicate_base(t_base **base, t_base **iso_base,
						int	map_x_size, int map_y_size)
{
	int		x_i;
	int		y_i;

	x_i = -1;
	while (++x_i < map_x_size)
	{
		y_i = -1;
		while (++y_i < map_y_size)
			iso_base[x_i][y_i] = base[x_i][y_i];
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
