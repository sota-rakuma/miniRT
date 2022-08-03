CC:=cc
CFLAGS:=-O2#-Wall -Wextra -Werror
NAME:=miniRT

SRC := $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
DEP := $(SRC:src/%.c=obj/%.d)

OBJ_DIR := $(sort $(dir $(OBJ)))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

LIBFT := ft
LIBFT_DIR := libft

MLX_DIR := minilibx-linux
OS := $(shell uname)
ifeq ($(OS), Linux)
LIBS_DIR := /usr/lib
MLX := mlx_Linux
LIBS := -lXext -lX11 -lm -lz
DEBUGFLAGS := -g -fsanitize=address -fsanitize=leak -fsanitize=undefined
else
MLX := mlx_Darwin
LIBS_DIR := /usr/X11R6/lib
LIBS := -lX11 -lXext -framework OpenGL -framework AppKit
DEBUGFLAGS :=
endif

DEPSFLAGS := -MMD -MP

all: $(NAME)

$(NAME): $(MLX_DIR)/lib$(MLX).a $(LIBFT_DIR)/lib$(LIBFT).a $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) \
		-L$(LIBFT_DIR) -l$(LIBFT) \
		-L$(MLX_DIR) -l$(MLX) \
		-L$(LIBS_DIR) $(LIBS)

$(MLX_DIR)/lib$(MLX).a:
	make -C $(MLX_DIR)

$(LIBFT_DIR)/lib$(LIBFT).a:
	make bonus -C $(LIBFT_DIR)

obj/%.o: src/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPSFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

norm:
	norminette src libft | grep Error! || echo ok

.PHONY: all clean fclean 
