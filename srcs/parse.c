#include "../includes/fdf.h"

int	get_x_size(char *file)
{
	int		fd;
	char	*line;
	int		lines_n;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("error: invalid file name");
	lines_n = 0;
	while (get_next_line(fd, &line)  > 0)
	{ 
		lines_n++;
		printf("%s\n", line); //AAAAAAAAAAa
		free(line);
		line = NULL;
	}
	close(fd);
	return (lines_n);
}

int	get_y_size(char *filename)
{
	int		fd;
	char	*line;
	int		elems_n;
	int		elems_n_tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("error: invalid file name");
	elems_n = -1;
	while (get_next_line(fd, &line) > 0)
	{
		elems_n_tmp = elems_n;
		elems_n = -1;
		while (line[++elems_n]);
		printf("%d\n", elems_n);
		printf("%d\n", elems_n_tmp);
		if (elems_n != elems_n_tmp && elems_n_tmp != -1)
			error("error: invalid map");
		free(line);
	}
	close(fd);
	return (elems_n);
}

t_data	file_reader(char *filename)
{
	int	map_x_size;
	int	map_y_size;

	t_data	data_tmp;
	map_x_size = get_x_size(filename);
	map_y_size = get_y_size(filename);
	printf("%d, %d\n", map_x_size, map_y_size);
	return(data_tmp);
}