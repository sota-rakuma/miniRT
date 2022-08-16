CC:=cc
CFLAGS:=-Wall -Wextra -Werror
NAME:=miniRT

SRC := \
	src/camera/camera.c \
	src/color/color.c \
	src/color/color_2.c \
	src/compute/compute.c \
	src/compute/compute2.c \
	src/display/display.c \
	src/event.c \
	src/img.c \
	src/light/light.c \
	src/main.c \
	src/shape/shape.c \
	src/shape/shape_normal_vec.c \
	src/shape/with_shape.c \
	src/util/double_max.c \
	src/util/double_min.c \
	src/util/free_all.c \
	src/util/ft_printf_and_exit.c \
	src/util/ft_xalloc.c \
	src/util/strs_len.c \
	src/util/usage.c \
	src/util/is_number.c \
	src/util/is_float.c \
	src/vec3d/vec3d_camera.c \
	src/vec3d/vec3d_camera_to_screen.c \
	src/vec3d/vec3d_sp_center.c \
	src/vec3d/vec3d_utils.c \
	src/vec3d/vec3d_utils1.c \
	src/world/world.c \
	src/world/world_add.c \
	src/world/world_parse_1.c \
	src/world/world_parse_2.c  \
	src/world/world_parse_3.c \
	src/world/world_parse_4.c \
	src/world/world_parse_utills.c \

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

ifeq ($(MAKECMDGOALS), bonus)
BONUSFLAGS = -D BONUS
endif

all: $(NAME)

$(NAME): $(MLX_DIR)/lib$(MLX).a $(LIBFT_DIR)/lib$(LIBFT).a $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(BONUSFLAGS) -o $(NAME) $(OBJ) \
		-L$(LIBFT_DIR) -l$(LIBFT) \
		-L$(MLX_DIR) -l$(MLX) \
		-L$(LIBS_DIR) $(LIBS)

$(MLX_DIR)/lib$(MLX).a:
	make -C $(MLX_DIR)

$(LIBFT_DIR)/lib$(LIBFT).a:
	make bonus -C $(LIBFT_DIR)

obj/%.o: src/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPSFLAGS) $(BONUSFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)
	# make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	# make clean -C $(MLX_DIR)
	# make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

norm_file:
	norminette src libft | grep Error! || echo ok

norm:
	@norminette src/*.c src/*/*.c libft/*.c libft/*/*.c  \
		| grep Error \
		| grep -v "TOO_MANY_FUNC" \
		| grep -v "WRONG_SCOPE_COMMENT" \
		|| echo ok

ok:
	cd .test && cat test.sh ok.sh > tmp.sh && bash tmp.sh

ng:
	cd .test && cat test.sh ng.sh > tmp.sh && bash tmp.sh

ok_bonus:
	cd .test && cat test.sh ok_bonus.sh > tmp.sh && bash tmp.sh

ng_bonus:
	cd .test && cat test.sh ng_bonus.sh > tmp.sh && bash tmp.sh

.PHONY: all clean fclean re
