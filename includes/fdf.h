#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include "../minilibx-linux/mlx.h" 
#include "../libft/get_next_line.h"

# define KEY_ESC 65307

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3

typedef struct s_base
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_base;


typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixcel;
	int		line_length;
	int		endian;
	t_base	**base;
}	t_data;

t_data	file_reader(char *filename);

void	error(char *err_msg);
