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
	free(strstr);
	strstr = NULL;
	return ;
}

static int
	atoui_convert(char c, int base)
{
	int		res;

	res = 0;
	if (c >= '0' && c <= '9')
		res = c - '0';
	else if (c >= 'A' && c <= 'F')
		res = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		res = c - 'a' + 10;
	if (res >= base)
		res = 0;
	return (res);
}

static int
	power(int nb, int power)
{
	int		res;

	res = 1;
	while (power-- > 0)
		res *= nb;
	return (res);
}

unsigned int
	ft_atoui_base(char *s, int base)
{
	int		len;
	int		pos;
	int		res;

	len = ft_strlen(s);
	pos= 0;
	res = 0;
	while (len-- > 0)
		res += atoui_convert(s[len], base) * power(base, pos++);
	return (res);
}
