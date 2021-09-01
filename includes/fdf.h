#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>		// DEBUG
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <X11/Xlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include "../includes/mlx.h" 
# include "../includes/libft.h" 

# define WIN_W 1920
# define WIN_H 1080

# define KEY_ESC 65307
# define KEY_ARROW_UP 65362
# define KEY_ARROW_DOWN 65364
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_LEFT 65361
# define KEY_8 56
# define KEY_9 57
# define KEY_PLUS 59
# define KEY_MINUS 45
# define KEY_M 109
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3

# define X_LINE 0
# define Y_LINE 1 

# define BUFFER_SIZE 1024

enum	e_point
{
	X,
	Y,
	Z,
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
	int		move_x;
	int		move_y;
	int		move_z;
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
	float		default_magnification[3];
	t_base		**base;
	t_base		**iso_base;
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

/*
** zoom.c
*/
float			calc_default_xy_magnification(int map_x_size, int map_y_size);
float			calc_default_z_magnification(t_data *data);
void			zoom(int key, t_data *data);

/*
** rotate.c
*/
void			rotate_x(float *y, float *z, float theta_x);
void			rotate_y(float *x, float *z, float theta_y);
void			rotate_z(float *x, float *y, float theta_z);
void			rotate(int key, t_data *data);

/*
** move_bonus.c
*/
void			move(int key, t_data *data);

/*
** parse.c
*/
int				get_x_size(char *file);
int				get_y_size(char *filename);
void			parse(char *filename, t_base **base,
					int map_x_size, int map_y_size);

/*
** draw_image.c draw_image_bonus.c
*/
void			draw_image(t_data *data);
void			draw_image_military(t_data *data);

/*
** draw_image_utils.c
*/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			duplicate_base(t_base **base, t_base **iso_base,
					int	map_x_size, int map_y_size);
void			convert_isometric_base(float *x, float *y, int z);

/*
** draw_image_line.c
*/
void			draw_line(t_data *data, int x_i, int y_i, int calc_type);

void			error(char *err_msg);
#endif