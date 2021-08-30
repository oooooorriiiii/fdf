#include "../includes/fdf.h"

void	rotate_x(float *y, float *z, float theta_x)
{
	int	pre_y;
	int	pre_z;

	pre_y = *y;
	pre_z = *z;
	*y = pre_y * cosf(theta_x) + pre_z * sinf(theta_x);
	*z = -pre_y * sinf(theta_x) + pre_z * cosf(theta_x);
}

void	rotate(int key, t_data *data)
{
	if (key == KEY_ARROW_UP)
		data->camera->theta_x += 0.1;
	else if (key == KEY_ARROW_DOWN)
		data->camera->theta_x -= 0.1;
	ft_bzero(data->addr,
		WINDOW_WIDTH * WINDOW_HEIGHT * (data->bits_per_pixcel / 8));
	draw_image(data);
}
