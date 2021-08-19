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

void	draw_image(t_data *data)
{
	draw_line(data, 200, 200, 500, 200);
	draw_line(data, 500, 200, 500, 500);
	draw_line(data, 500, 500, 200, 500);
	draw_line(data, 200, 500, 200, 200);
	draw_line(data, 350, 200, 350, 500);
	draw_line(data, 200, 350, 500, 350);
	draw_line(data, 200, 200, 500, 500);
	draw_line(data, 200, 500, 500, 200);
}
