/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymori <ymori@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:10:46 by ymori             #+#    #+#             */
/*   Updated: 2021/02/18 01:37:25 by ymori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	s_i;
	size_t	p_i;

	s_i = start;
	p_i = 0;
	if (!(p = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (p_i < len && s_i < ft_strlen(s))
		p[p_i++] = s[s_i++];
	p[p_i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1) + 1;
	if (!(p = malloc(sizeof(char) * len)))
		return (NULL);
	while (len--)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*p;
	size_t		p_i;
	size_t		s_i;

	if (!s1 || !s2)
		return (NULL);
	if (!(p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	p_i = 0;
	s_i = 0;
	while (s1[s_i] != '\0')
		p[p_i++] = s1[s_i++];
	s_i = 0;
	while (s2[s_i] != '\0')
		p[p_i++] = s2[s_i++];
	p[p_i] = '\0';
	return (p);
}
