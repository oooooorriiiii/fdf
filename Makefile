NAME	=	fdf

CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	main.c
OBJS	=	$(SRCS:%.c=%.o)

MLX_DIR		=	minilibx-linux
LIBFT_DIR	=	libft

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(MLX_DIR) libft/libft.a -lmlx -lXext -lX11  -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)