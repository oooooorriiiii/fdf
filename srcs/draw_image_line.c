#include "../includes/fdf.h"

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
		calc.err2 = 2 * calc.err;
		if (calc.err2 >= calc.dy)
		{
			calc.err += calc.dy;
			calc.x += calc.sx;
		}
		if (calc.err2 <= calc.dx)
		{
			calc.err += calc.dx;
			calc.y += calc.sy;
		}
	}
}
