CC:=cc
CFLAGS:=#-Wall -Wextra -Werror
NAME:=miniRT
INCLUDE:=include
SRC_DIR:=src
SRC:=$(wildcard src/*.c)
SRC:=$(subst src/, , $(SRC))
LIBFT:=ft
LIBFT_DIR:=libft

MLX_DIR:=minilibx-linux
OS := $(shell uname)
ifeq ($(OS), Linux)
LIBS_DIR:=/usr/lib
MLX:=mlx_Linux
LIBS:=-lXext -lX11 -lm -lz
DEBUGFLAGS:=-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
else
MLX:=mlx_Darwin
LIBS_DIR:=/usr/X11R6/lib
LIBS:=-lX11 -lXext -framework OpenGL -framework AppKit
DEBUGFLAGS:=
endif

OBJ_DIR:=obj
ifdef TEST
CXXFLAGS+=-DTEST
endif
DEP_DIR:=dep
OBJ:=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP:=$(addprefix $(DEP_DIR)/, $(SRC:.c=.d))

all: $(NAME)

$(NAME): $(MLX_DIR)/lib$(MLX).a $(LIBFT_DIR)/lib$(LIBFT).a $(OBJ_DIR) $(DEP_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -l$(LIBFT) -L$(MLX_DIR) -l$(MLX) -L$(LIBS_DIR) $(LIBS)

$(MLX_DIR)/lib$(MLX).a:
	make -C $(MLX_DIR)

$(LIBFT_DIR)/lib$(LIBFT).a:
	make bonus -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR);

$(DEP_DIR):
	@mkdir -p $(DEP_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -I$(MLX_DIR) -I$(INCLUDE) -I$(LIBFT_DIR) -c -o $@ $<
	@mv $(OBJ_DIR)/*.d $(DEP_DIR)/

-include $(DEP)

clean:
	rm -fR $(OBJ_DIR) $(DEP_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re