NAME=miniRT

CC=cc

CFLAGS=-Wall -Wextra -Werror

SRC_DIR=src

OBJ_DIR=obj

SRCS=	vector_utils.c \
		main.c

OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MINILIB_DIR = minilibx-linux/
LDFLAGS = -L$(MINILIB_DIR)
LDLIBS = -lm -L/usr/X11R6/lib -L minilibx-linux -lmlx -lX11 -lXext -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) minilibx-linux/libmlx.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I/includes/.

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
