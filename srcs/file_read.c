#include "../includes/fdf.h"

t_data	file_reader(char *filename)
{
	t_data	data;

	data.map_x_size = get_x_size(filename);
	data.map_y_size = get_y_size(filename);
	data.base = create_map(data.map_x_size, data.map_y_size);
	parse(filename, data.base, data.map_x_size, data.map_y_size);
	data.iso_base = create_map(data.map_x_size, data.map_y_size);
	init_data(&data);
	return (data);
}
