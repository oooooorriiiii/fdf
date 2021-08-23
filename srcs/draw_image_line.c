#include "../includes/fdf.h"

static t_calc	init_calc(float x0, float y0, float x1, float y1)
{
	t_calc	calc;

	if (x1 >= x0)
		calc.dx = x1 - x0;
	else
		calc.dx = x0 - x1;
	if (y1 >= y0)
		calc.dy = y0 - y1;
	else
		calc.dy = y1 - y0;
	if (x0 < x1)
		calc.sx = 1;
	else
		calc.sx = -1;
	if (y0 < y1)
		calc.sy = 1;
	else
		calc.sy = -1;
	calc.err = calc.dx + calc.dy;
	calc.x = x0;
	calc.y = y0;
	return (calc);
}

static void	draw_line_loop(t_data *data, t_calc calc, int x1, int y1)
{
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

/*
** To support norm, two points are calculated inside this function.
** Therefore, the appropriateness of the two points must be checked
** outside the function.
*/
void	draw_line(t_data *data, int x_i, int y_i, int calc_type)
{
	t_calc	calc;
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	x0 = data->isometric_base[x_i][y_i].x;
	y0 = data->isometric_base[x_i][y_i].y;
	x1 = 0;
	y1 = 0;
	if (calc_type == X_LINE)
	{
		x1 = data->isometric_base[x_i + 1][y_i].x;
		y1 = data->isometric_base[x_i + 1][y_i].y;
	}
	if (calc_type == Y_LINE)
	{
		x1 = data->isometric_base[x_i][y_i + 1].x;
		y1 = data->isometric_base[x_i][y_i + 1].y;
	}
	calc = init_calc(x0, y0, x1, y1);
	draw_line_loop(data, calc, x1, y1);
}
