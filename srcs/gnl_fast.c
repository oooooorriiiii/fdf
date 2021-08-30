#include "../includes/fdf.h"

int	buffered_getc_fd(int fd)
{
	static char		buf[BUFFER_SIZE];
	static ssize_t	ret;
	static ssize_t	pos;

	if (pos == ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		pos = 0;
	}
	if (0 < ret)
		return (buf[pos++]);
	else
		return (ret - 1);
}

int	resize_str(char **str_p, size_t allocate_size)
{
	char	*tmp;
	size_t	i;

	tmp = *str_p;
	*str_p = malloc(allocate_size + 1);
	if (!(*str_p))
	{
		free(tmp);
		return (0);
	}
	i = 0;
	while (tmp[i] && i < allocate_size)
	{
		(*str_p)[i] = tmp[i];
		i++;
	}
	(*str_p)[i] = '\0';
	free(tmp);
	return (1);
}

int	padding_char_to_str(int	c, int *str_i, char **ret_str)
{
	int		i;

	i = *str_i;
	if (c == '\n')
	{
		(*ret_str)[i] = '\0';
		return (0);
	}
	else
	{
		(*ret_str)[i] = c;
		(*ret_str)[++i] = '\0';
	}
	*str_i = i;
	return (1);
}

int	ret_val(int c)
{
	if (c >= 0)
		return (1);
	else
		return (0);
}

int	gnl_fast(int fd, char **line)
{
	char	*ret_str;
	int		c;
	int		str_i;

	ret_str = malloc(2);
	if (!ret_str)
		return (-1);
	ret_str[0] = '\0';
	str_i = 0;
	c = buffered_getc_fd(fd);
	while (c >= 0)
	{
		if (str_i && !(str_i & (str_i - 1)) && !resize_str(&ret_str, str_i * 2))
			return (-1);
		if (!padding_char_to_str(c, &str_i, &ret_str))
			break ;
		c = buffered_getc_fd(fd);
	}
	if (c == -2)
	{
		free (ret_str);
		return (-1);
	}
	*line = ret_str;
	return (ret_val(c));
}
