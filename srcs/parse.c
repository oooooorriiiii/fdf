#include "../includes/fdf.h"

int	parse_line(int fd, char ***parse_line)
{
	char	*line;
	int		line_i;

	if (gnl_fast(fd, &line) == 0)
	{
		free(line);
		return (0);
	}
	line_i = -1;
	while (line[++line_i])
		if (line[line_i] == '\t')
			line[line_i] = ' ';
	*parse_line = ft_split(line, ' ');
	ft_strfree(&line);
	return (1);
}

int	get_x_size(char *file)
{
	int		fd;
	char	*line;
	int		lines_n;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("error: invalid file name");
	lines_n = 0;
	while (gnl_fast(fd, &line) > 0)
	{
		lines_n++;
		ft_strfree(&line);
	}
	ft_strfree(&line);
	close(fd);
	return (lines_n);
}

int	get_y_size(char *filename)
{
	int		fd;
	char	**line;
	int		elems_n;
	int		elems_n_tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("error: invalid file name");
	elems_n = -1;
	while (parse_line(fd, &line) != 0)
	{
		elems_n_tmp = elems_n;
		elems_n = 0;
		while (line[elems_n])
			elems_n++;
		if (elems_n != elems_n_tmp && elems_n_tmp != -1)
			error("error: invalid map");
		ft_strstrfree(line);
	}
	close(fd);
	return (elems_n);
}

void	parse(char *filename, t_base **base, int map_x_size, int map_y_size)
{
	char	**parsed_line;
	char	**z_and_color;
	int		fd;
	int		x_i;
	int		y_i;

	fd = open(filename, O_RDONLY);
	x_i = -1;
	while (++x_i < map_x_size)
	{
		parse_line(fd, &parsed_line);
		y_i = -1;
		while (++y_i < map_y_size)
		{
			base[x_i][y_i].x = y_i - map_y_size / 2;
			base[x_i][y_i].y = x_i - map_x_size / 2;
			z_and_color = ft_split(parsed_line[y_i], ',');
			base[x_i][y_i].z = ft_atoi(z_and_color[0]);
			if (z_and_color[1])
				base[x_i][y_i].color = ft_atoui_base(z_and_color[1], 16);
			ft_strstrfree(z_and_color);
			if (base[x_i][y_i].color == 0)
				base[x_i][y_i].color = 0x0000FF00;
		}
		ft_strstrfree(parsed_line);
	}
	close(fd);
}

t_data	file_reader(char *filename)
{
	t_data	data;

	data.map_x_size = get_x_size(filename);
	data.map_y_size = get_y_size(filename);
	data.base = create_map(data.map_x_size, data.map_y_size);
	parse(filename, data.base, data.map_x_size, data.map_y_size);
	data.isometric_base = create_map(data.map_x_size, data.map_y_size);
	init_data(&data);
	return (data);
}
