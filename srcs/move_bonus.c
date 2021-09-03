#include "../includes/fdf.h"

void	move(int key, t_data *data)
{
	if (key == KEY_W)
		data->camera->move_y -= 10;
	else if (key == KEY_A)
		data->camera->move_x -= 10;
	else if (key == KEY_S)
		data->camera->move_y += 10;
	else if (key == KEY_D)
		data->camera->move_x += 10;
	ft_bzero(data->addr,
		WIN_W * WIN_H * (data->bits_per_pixcel / 8));
	draw_image(data);
}
