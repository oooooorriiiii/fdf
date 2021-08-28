#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <X11/Xlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include "../minilibx-linux/mlx.h" 
# include "../libft/get_next_line.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define KEY_ESC 65307
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define X_LINE 0
# define Y_LINE 1 

enum	e_point
{
	X,
	Y,
};

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
	int	color;
}	t_calc;

typedef struct s_base
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_base;

typedef struct s_camera
{
	int		zoom;
	float	theta_x;
	float	theta_y;
	float	theta_z;
}	t_camera;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixcel;
	int			line_length;
	int			endian;
	int			map_x_size;
	int			map_y_size;
	t_base		**base;
	t_base		**isometric_base;
	t_camera	*camera;
	float		height;
}	t_data;

t_data			file_reader(char *filename);

void			*ft_malloc_zero(size_t size);
void			ft_strstrfree(char **strstr);
unsigned int	ft_atoui_base(char *s, int base);

int				gnl_fast(int fd, char **line);

void			init_data(t_data *data);
t_base			**create_map(int x_size, int y_size);

int				get_x_size(char *file);
int				get_y_size(char *filename);
void			parse(char *filename, t_base **base,
					int map_x_size, int map_y_size);

void			draw_image(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

void			draw_line(t_data *data, int x_i, int y_i, int calc_type);

void			error(char *err_msg);
#endif