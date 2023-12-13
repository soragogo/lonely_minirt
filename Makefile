NAME=miniRT

CC=cc

CFLAGS=-Wall -Wextra -Werror

SRC_DIR=src

OBJ_DIR=obj

LIBFTDIR=libft
LIBFT=$(LIBFTDIR)/libft.a
LIBFT_INCLUDE=-I$(LIBFTDIR)
LIBFT_LINK=-L$(LIBFTDIR) -lft

SRCS=	 add_ambient.c \
		add_camera.c \
		add_elements_utils.c \
		add_light.c \
		add_objects.c \
		atod.c \
		error_handling.c \
		free_utils.c \
		get_next_line.c \
		get_next_line_utils.c \
		init_world.c \
		main.c \
		read_map.c \
		debug.c \
		init_minilibx.c \
		event_hook.c \
		get_screen_start_position.c \
		vector_utils.c \
		draw_image.c \
		render_objects.c

OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MINILIB_DIR = minilibx-linux/
LDFLAGS = -L$(MINILIB_DIR)
LDLIBS = -lm -L/usr/X11R6/lib -L minilibx-linux -lmlx -lX11 -lXext -framework OpenGL -framework AppKit

ifeq ($(MAKECMDGOALS), debug)
	CC += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(LIBFT_LINK) minilibx-linux/libmlx.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I/includes/. $(LIBFT_INCLUDE)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

debug: fclean $(OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS) $(LIBFT_LINK) minilibx-linux/libmlx.a
