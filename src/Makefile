CXX:=c++
CXXFLAGS:=#-Wall -Wextra -Werror
DEBUGFLAGS:=-g -fsanitize=address -fsanitize=leak -fsanitize=undefined
NAME:=a.out
SRC:=test.cpp
MLX:=mlx_Linux
MLX_DIR:=minilibx-linux
LIBS_DIR:=/usr/lib
LIBS:=-lXext -lX11 -lm -lz
OBJ_DIR:=obj
ifdef TEST
CXXFLAGS+=-DTEST
endif
DEP_DIR:=dep
OBJ:=$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
DEP:=$(addprefix $(DEP_DIR)/, $(SRC:.cpp=.d))

-include $(DEP)

all: $(NAME)

ifdef DEBUG
$(NAME): $(OBJ_DIR) $(DEP_DIR) $(OBJ) $(MLX)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) -L$(MLX_DIR) -l$(MLX) -L$(LIBS_DIR) $(LIBS)
else
$(NAME): $(OBJ_DIR) $(DEP_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -L$(MLX_DIR) -l$(MLX) -L$(LIBS_DIR) $(LIBS)
endif

$(MLX):
	make -c $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR);

$(DEP_DIR):
	@mkdir -p $(DEP_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -I$(MLX_DIR) -c -o $@ $<
	@mv $(OBJ_DIR)/*.d $(DEP_DIR)/

clean:
	rm -fR $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re