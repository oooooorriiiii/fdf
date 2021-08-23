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
