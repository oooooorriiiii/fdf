#include "../includes/fdf.h"

static t_camera	*init_camera_data(t_data *data)
{
	t_camera	*ret_camera_struct_ptr;

	ret_camera_struct_ptr = ft_malloc_zero(sizeof(t_camera));
	if (ret_camera_struct_ptr == NULL)
		error("failed malloc");
	ret_camera_struct_ptr->zoom = WIN_W / (2 * data->map_y_size);
	ret_camera_struct_ptr->theta_x = 0;
	ret_camera_struct_ptr->theta_y = 0;
	ret_camera_struct_ptr->theta_z = 0;
	ret_camera_struct_ptr->move_x = 0;
	ret_camera_struct_ptr->move_y = 0;
	ret_camera_struct_ptr->move_z = 0;
	return (ret_camera_struct_ptr);
}

void	init_data(t_data *data)
{
	data->camera = init_camera_data(data);
	data->height = 0;
	data->default_magnification[X] = calc_default_xy_magnification(
			data->map_x_size, data->map_y_size);
	data->default_magnification[Y] = data->default_magnification[X];
	data->default_magnification[Z] = calc_default_z_magnification(data);
}

t_base	**create_map(int x_size, int y_size)
{
	t_base	**base;
	int		x_i;

	base = (t_base **)ft_malloc_zero(sizeof(t_base *) * x_size);
	x_i = -1;
	while (++x_i < x_size)
		base[x_i] = (t_base *)ft_malloc_zero(sizeof(t_base) * y_size);
	return (base);
}
