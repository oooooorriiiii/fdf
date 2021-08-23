NAME	=	fdf

CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/main.c \
			srcs/parse.c \
			srcs/draw_image.c \
			srcs/draw_image_line.c \
			srcs/error.c
OBJS	=	$(SRCS:%.c=%.o)

MLX_DIR		=	minilibx-linux
LIBFT_DIR	=	libft

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -fsanitize=address -L$(MLX_DIR) libft/libft.a -lmlx -lXext -lX11  -o $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(OBJS) -L$(MLX_DIR) libft/libft.a -lmlx -lXext -lX11  -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean:	clean
	rm -f $(NAME)

.PHONY:	re
re:	fclean all
