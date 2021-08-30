NAME	=	fdf

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRCS_DIR	=	srcs/
LIB_DIR		=	libs

SRCS	=	$(SRCS_DIR)main.c \
			$(SRCS_DIR)parse.c \
			$(SRCS_DIR)init.c	\
			$(SRCS_DIR)zoom.c	\
			$(SRCS_DIR)rotate.c	\
			$(SRCS_DIR)draw_image.c \
			$(SRCS_DIR)draw_image_utils.c	\
			$(SRCS_DIR)draw_image_line.c \
			$(SRCS_DIR)utils.c	\
			$(SRCS_DIR)gnl_fast.c	\
			$(SRCS_DIR)file_read.c	\
			$(SRCS_DIR)error.c

BONUS	=	$(SRCS_DIR)draw_image_bonus.c \
			$(SRCS_DIR)main_bonus.c	\
			$(SRCS_DIR)parse.c \
			$(SRCS_DIR)init.c	\
			$(SRCS_DIR)zoom.c	\
			$(SRCS_DIR)rotate.c	\
			$(SRCS_DIR)draw_image_utils.c	\
			$(SRCS_DIR)draw_image_line.c \
			$(SRCS_DIR)utils.c	\
			$(SRCS_DIR)gnl_fast.c	\
			$(SRCS_DIR)file_read.c	\
			$(SRCS_DIR)error.c

OBJS		=	$(SRCS:%.c=%.o)
BONUS_OBJS	=	$(BONUS:%.c=%.o)

.SUFFIXES:	.o .c

MLX_DIR		=	minilibx-linux
LIBFT_DIR	=	$(LIB_DIR)/libft
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR)/,$(LIBFT_NAME))

.PHONY:	all
all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -L$(MLX_DIR) \
		$(LIBFT_DIR)/$(LIBFT_NAME) -lm -lmlx -lXext -lX11  -o $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(OBJS) -L$(MLX_DIR) libft/libft.a -lmlx -lXext -lX11  -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) $(LIBFT_NAME)

.PHONY: bonus
bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -fsanitize=address -L$(MLX_DIR) \
		$(LIBFT_DIR)/$(LIBFT_NAME) -lm -lmlx -lXext -lX11  -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

.PHONY: fclean
fclean:	clean
	rm -f $(NAME)

.PHONY:	re
re:	fclean all
