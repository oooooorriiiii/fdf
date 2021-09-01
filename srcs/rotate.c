#include "../includes/fdf.h"

void	rotate_x(float *y, float *z, float theta_x)
{
	float	pre_y;
	float	pre_z;

	pre_y = *y;
	pre_z = *z;
	*y = pre_y * cosf(theta_x) + pre_z * sinf(theta_x);
	*z = -pre_y * sinf(theta_x) + pre_z * cosf(theta_x);
}

void	rotate_y(float *x, float *z, float theta_y)
{
	float	pre_x;
	float	pre_z;

	pre_x = *x;
	pre_z = *z;
	*x = pre_x * cosf(theta_y) + pre_z * sinf(theta_y);
	*z = -pre_x * sinf(theta_y) + pre_z * cosf(theta_y);
}

void	rotate_z(float *x, float *y, float theta_z)
{
	float	pre_x;
	float	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = pre_x * cosf(theta_z) - pre_y * sinf(theta_z);
	*y = pre_x * sinf(theta_z) + pre_y * cosf(theta_z);
}

void	rotate(int key, t_data *data)
{
	if (key == KEY_ARROW_UP)
		data->camera->theta_x += 0.1;
	else if (key == KEY_ARROW_DOWN)
		data->camera->theta_x -= 0.1;
	else if (key == KEY_ARROW_RIGHT)
		data->camera->theta_y += 0.1;
	else if (key == KEY_ARROW_LEFT)
		data->camera->theta_y -= 0.1;
	else if (key == KEY_8)
		data->camera->theta_z += 0.1;
	else if (key == KEY_9)
		data->camera->theta_z -= 0.1;
	ft_bzero(data->addr,
		WIN_W * WIN_H * (data->bits_per_pixcel / 8));
	draw_image(data);
}
