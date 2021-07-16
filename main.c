#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include "./minilibx-linux/mlx.h" 
#include "./get_next_line/get_next_line.h"

# define KEY_ESC 65307

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3

typedef struct s_view
{
	void	*mlx;
	void	*win;
}	t_view;

int	closer(int keycode, t_view *view)
{
	(void)keycode;
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
}

int	key_hook(int key, void *v)
{
	t_view	*view;

	view = (t_view *)v;
	printf("key = %d\n", key); // DEBUG
	if (key == KEY_ESC)
		closer(KEY_ESC, view);
	return (0);
}

int	get_x(char *file)
{
	int	fd;
	char	*line;
	int	lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("error: invalid file name");
	lines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);

}

t_view	file_reader(char *filename)
{
	t_view	view_tmp;
	printf("%d\n", get_x(filename));
	return(view_tmp);
}


int	main(int args, char **argv)
{
	t_view	view;

	(void)args;
	view = file_reader(argv[1]);
	view.mlx = mlx_init();
	view.win = mlx_new_window(view.mlx, 1920, 1080, "fdf");
	mlx_hook(view.win, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, key_hook, &view);
	mlx_loop(view.mlx);
	return (0);
}
