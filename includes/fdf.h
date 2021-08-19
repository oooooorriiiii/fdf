#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include "../minilibx-linux/mlx.h" 
#include "../libft/get_next_line.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define KEY_ESC 65307

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3

typedef struct s_calc
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}	t_calc;


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
	int		map_x_size;
	int		map_y_size;
	t_base	**base;
}	t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

t_data	file_reader(char *filename);

void	draw_image(t_data *data);

void	error(char *err_msg);
