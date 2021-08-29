NAME	=	fdf

CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror

SRCS_DIR	=	srcs/

SRCS	=	$(SRCS_DIR)main.c \
			$(SRCS_DIR)parse.c \
			$(SRCS_DIR)init.c	\
			$(SRCS_DIR)zoom.c	\
			$(SRCS_DIR)draw_image.c \
			$(SRCS_DIR)draw_image_line.c \
			$(SRCS_DIR)utils.c	\
			$(SRCS_DIR)gnl_fast.c	\
			$(SRCS_DIR)file_read.c	\
			$(SRCS_DIR)error.c
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
