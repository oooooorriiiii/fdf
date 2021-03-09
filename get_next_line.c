/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:10:27 by ymori             #+#    #+#             */
/*   Updated: 2021/03/09 21:35:20 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	found_newline(char *str)
{
	size_t		i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		str_free(char **p)
{
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}

static int	set_up_line(ssize_t read_size, char **loaded_str,\
						char **line, int fd)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (loaded_str[fd][i] != '\n' && loaded_str[fd][i] != '\0')
		i++;
	if (loaded_str[fd][i] == '\n')
	{
		*line = ft_substr(loaded_str[fd], 0, i);
		tmp = ft_strdup(&loaded_str[fd][i + 1]);
		free(loaded_str[fd]);
		loaded_str[fd] = tmp;
		if (loaded_str[fd][0] == '\0')
			str_free(&loaded_str[fd]);
	}
	else
	{
		*line = ft_strdup(loaded_str[fd]);
		str_free(&loaded_str[fd]);
		if (read_size == 0 && loaded_str[fd] == NULL)
			return (0);
	}
	return (1);
}

static int	return_process(ssize_t read_size, char **loaded_str,\
						char **line, int fd)
{
	if (read_size < 0)
		return (-1);
	else if (read_size == 0 && loaded_str[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (set_up_line(read_size, loaded_str, line, fd));
}

int			get_next_line(int fd, char **line)
{
	static char	*loaded_str[OPEN_MAX];
	char		*buf_str;
	char		*tmp;
	ssize_t		read_size;

	if (!line || (fd < 0 || fd >= OPEN_MAX) || \
		!(buf_str = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((read_size = read(fd, buf_str, BUFFER_SIZE)) > 0)
	{
		buf_str[read_size] = '\0';
		if (loaded_str[fd] == NULL)
			loaded_str[fd] = ft_strdup(buf_str);
		else
		{
			tmp = ft_strjoin(loaded_str[fd], buf_str);
			free(loaded_str[fd]);
			loaded_str[fd] = tmp;
		}
		if (found_newline(loaded_str[fd]))
			break ;
	}
	free(buf_str);
	return (return_process(read_size, loaded_str, line, fd));
}
