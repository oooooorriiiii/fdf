#include "../includes/fdf.h"

void	*ft_malloc_zero(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size);
	return (ptr);
}

void	ft_strstrfree(char **strstr)
{
	int	i;

	i = -1;
	if (!strstr)
		return ;
	while (strstr[++i])
		ft_strfree(&strstr[i]);
	ft_strfree(strstr);
	strstr = NULL;
	return ;
}

int	parse_line(int fd, char ***parse_line)
{
	char	*line;
	int		line_i;

	if (get_next_line(fd, &line) == 0)
		return (0);
	line_i = -1;
	while (line[++line_i])
		if (line[line_i] == '\t')
			line[line_i] = ' ';
	*parse_line = ft_split(line, ' ');
	ft_strstrfree(&line);
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
	while (get_next_line(fd, &line)  > 0)
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
	while (parse_line(fd, &line) > 0)
	{
		elems_n_tmp = elems_n;
		elems_n = -1;
		while (line[++elems_n]);
		if (elems_n != elems_n_tmp && elems_n_tmp != -1)
			error("error: invalid map");
		ft_strstrfree(line);
	}
	ft_strstrfree(line);
	close(fd);
	return (elems_n);
}


void	parse(char *filename, t_base **base, int map_x_size, int map_y_size)
{
	char	**parsed_line;
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
			base[x_i][y_i].z = ft_atoi(parsed_line[y_i]);
			base[x_i][y_i].color = 0x00FF00;
		}
		ft_strstrfree(parsed_line);
	}
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

t_data	file_reader(char *filename)
{
	int	map_x_size;
	int	map_y_size;
	t_data	data_tmp;

	map_x_size = get_x_size(filename);
	map_y_size = get_y_size(filename);
	data_tmp.base = create_map(map_x_size, map_y_size);
	parse(filename, data_tmp.base ,map_x_size, map_y_size);

	return(data_tmp);
}