#include "../includes/fdf.h"

void	error(char *err_msg)
{
	ft_putendl_fd(err_msg, STDOUT_FILENO);
	exit(0);
}
