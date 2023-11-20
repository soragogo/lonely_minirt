NAME=miniRT

CC=cc

CFLAGS=-Wall -Wextra -Werror

SRC_DIR=src

OBJ_DIR=obj

LIBFTDIR=libft
LIBFT=$(LIBFTDIR)/libft.a
LIBFT_INCLUDE=-I$(LIBFTDIR)
LIBFT_LINK=-L$(LIBFTDIR) -lft

SRCS=	add_elements_utils.c \
		atod.c \
		error_handling.c \
		free_utils.c \
		get_next_line.c \
		get_next_line_utils.c \
		main.c \
		vector_utils.c

OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MINILIB_DIR = minilibx-linux/
LDFLAGS = -L$(MINILIB_DIR)
LDLIBS = -lm -L/usr/X11R6/lib -L minilibx-linux -lmlx -lX11 -lXext -framework OpenGL -framework AppKit

ifeq ($(MAKECMDGOAL), debug)
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
	$(CC) $(CFLAGS) -g -fsanitize=address $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS) $(LIBFT_LINK) minilibx-linux/libmlx.a
