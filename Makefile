NAME	=	fdf

CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	main.c
OBJS	=	$(SRCS:%.c=%.o)

MLX_DIR	=	minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(MLX_DIR) -lmlx -lXext -lX11  -o $(NAME)