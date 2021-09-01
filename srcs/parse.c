#include "../includes/fdf.h"

static int	parse_line(int fd, char ***parse_line)
{
	char	*line;
	int		line_i;

	if (gnl_fast(fd, &line) == 0 && line[0] == '\0')
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
	if (line[0] != '\0')
		lines_n++;
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

static void
	base_setup(t_base **base, char **parsed_line, int *map_size, int *i)
{
	char	**z_and_color;

	base[i[X]][i[Y]].x = i[Y] - map_size[Y] / 2;
	base[i[X]][i[Y]].y = i[X] - map_size[X] / 2;
	z_and_color = ft_split(parsed_line[i[Y]], ',');
	base[i[X]][i[Y]].z = ft_atoi(z_and_color[0]);
	if (z_and_color[1])
		base[i[X]][i[Y]].color = ft_atoui_base(z_and_color[1], 16);
	ft_strstrfree(z_and_color);
	if (base[i[X]][i[Y]].color == 0)
		base[i[X]][i[Y]].color = 0x0000FF00;
}

void	parse(char *filename, t_base **base, int map_x_size, int map_y_size)
{
	char	**parsed_line;
	int		fd;
	int		i[2];
	int		map_size[2];

	fd = open(filename, O_RDONLY);
	i[X] = -1;
	while (++i[X] < map_x_size)
	{
		parse_line(fd, &parsed_line);
		i[Y] = -1;
		while (++i[Y] < map_y_size)
		{
			map_size[X] = map_x_size;
			map_size[Y] = map_y_size;
			base_setup(base, parsed_line, map_size, i);
		}
		ft_strstrfree(parsed_line);
	}
	close(fd);
}
