NAME = cub3D

SRC_DIR = src
LIBMLX = ./MLX42
MXL = MLX42/build/libmlx42.a

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

CFLAGS = -Wall -Wextra -Werror -MMD
#FSANITIZE = -g3 -fsanitize=address
LIBFLAGS = -L./libft -lft -lm
MLXFLAGS = -Iinclude -ldl -lglfw -pthread
MY_HEADER = ./includes/

OBJ_DIR = obj

# Detect operating system
UNAME_S := $(shell uname -s)

# OS-specific settings
ifeq ($(UNAME_S),Linux)
    MLXFLAGS = -I$(LIBMLX)/include -ldl -lglfw -pthread
    DEPS_MSG = "Please install dependencies:\nsudo apt-get update && sudo apt-get install cmake make xorg libxext-dev zlib1g-dev libbsd-dev libglfw3-dev"
endif
ifeq ($(UNAME_S),Darwin)
    MLXFLAGS = -I$(LIBMLX)/include -framework Cocoa -framework OpenGL -framework IOKit -lglfw
    DEPS_MSG = "Please install dependencies:\nbrew update && brew install cmake glfw"
endif

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))
DEPS = $(OBJECTS:.o=.d)

# Check if the operating system is supported
check_os:
	@if [ "$(UNAME_S)" != "Linux" ] && [ "$(UNAME_S)" != "Darwin" ]; then \
		echo "Unsupported operating system"; \
		exit 1; \
	fi

# Check if all dependencies are installed
check_dependencies: check_os
	@which cmake > /dev/null || (echo "ERROR: cmake not found.\n$(DEPS_MSG)"; \
		exit 1)
ifeq ($(UNAME_S),Linux)
	@ldconfig -p | grep libglfw.so > /dev/null || (echo "ERROR: GLFW not found.\n$(DEPS_MSG)"; \
		exit 1)
endif
ifeq ($(UNAME_S),Darwin)
	@test -d /usr/local/include/GLFW || test -d /opt/homebrew/include/GLFW || (echo "ERROR: GLFW not found.\n$(DEPS_MSG)"; \
		exit 1)
endif

# Check if MLX42 submodule is initialized
check_submodules:
	@if [ ! -f "$(LIBMLX)/CMakeLists.txt" ]; then \
		echo "MLX42 submodule not found! Initializing submodules..."; \
		git submodule init && git submodule update; \
	fi

all: check_submodules check_dependencies libft42 $(NAME)

libft42:
	@make -C libft
	@if [ ! -d "$(LIBMLX)/build" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@
	@echo -n "Compiling src... $<\r"

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(MXL) $(LIBFLAGS) $(MLXFLAGS)

#include dependencies
-include $(DEPS)

debug: CLFAGS += -g
debug: re

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re debug libft42 check_dependencies check_submodules
