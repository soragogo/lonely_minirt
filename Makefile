NAME=miniRT

CC=cc

CFLAGS=-Wall -Wextra -Werror

SRC_DIR=src

OBJ_DIR=obj

SRCS=	vector_utils.c \
		main.c

OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I/includes/.

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
