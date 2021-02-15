/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:10:27 by ymori             #+#    #+#             */
/*   Updated: 2021/02/12 22:39:09 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 100000
#define FD_MAX 1025

int		found_LF(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*loaded_str[FD_MAX];
	char		buf_str[BUFFER_SIZE + 1];
	char		*tmp;
	int			read_size;
	int			i;

	if (!line || (fd < 0 || fd >= FD_MAX))
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
		if (found_LF(loaded_str[fd]))
			break ;
	}
	// TODO: return value handle, line <- loaded_str or buf_str
	i = 0;
	if (read_size < 0)
		return (-1);
	else if (read_size == 0 && loaded_str[fd] == NULL)
		return (0);
	else
	{
		while ((loaded_str[fd][i] != '\n' && loaded_str[fd][i] != '\0'))
			i++;
		if (loaded_str[fd][i] == '\n')
		{
			*line = ft_substr(loaded_str[fd], 0, i);
			tmp = ft_strdup(&loaded_str[fd][i + 1]);
			free(loaded_str[fd]);
			loaded_str[fd] = tmp;
			if (loaded_str[fd][0] == '\0')
			{
				free(loaded_str[fd]);
				loaded_str[fd] = NULL;
			}
		}
		else
		{
			*line = ft_strdup(loaded_str[fd]);
			free(loaded_str[fd]);
			loaded_str[fd] = NULL;
		}
		return (1);
	}
}
