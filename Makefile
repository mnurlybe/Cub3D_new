NAME = cub3D

SRC_DIR = src
OBJ_DIR = obj
LIBMLX = ./MLX42
MXL = MLX42/build/libmlx42.a

# Colors and formatting
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m
BOLD = \033[1m
CLEAR = \r\033[K

# Progress variables
TOTAL_FILES := $(shell find $(SRC_DIR) -name '*.c' | wc -l)
CURRENT_FILE = 0

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

CFLAGS = -Wall -Wextra -Werror -MMD
#FSANITIZE = -g3 -fsanitize=address
LIBFLAGS = -L./libft -lft -lm
MLXFLAGS = -Iinclude -ldl -lglfw -pthread
MY_HEADER = ./includes/


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

#OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

all: check_submodules check_dependencies libft42 $(NAME)
	@printf "$(GREEN)$(BOLD)✓ Build complete: $(NAME)$(RESET)\n"

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

doc:
	@if ! command -v doxygen &> /dev/null; then \
		echo "Error: doxygen not found. Please install doxygen:"; \
		echo "  Ubuntu/Debian: sudo apt-get install doxygen graphviz"; \
		echo "  macOS: brew install doxygen graphviz"; \
		exit 1; \
	fi
	@echo "Generating documentation..."
	@doxygen Doxyfile
	@echo "Documentation generated in docs/doxygen/html"
	@echo "Open docs/doxygen/html/index.html in your browser to view"


libft42:
	@make -C libft
	@if [ ! -d "$(LIBMLX)/build" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(MXL) $(LIBFLAGS) $(MLXFLAGS)
	@printf "$(GREEN)✓ Linking complete$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $(OBJECTS))
	@$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "[%3d%%]$(GREEN) Compiling %s $(RESET)\n" "$$(( $(CURRENT_FILE) * 100 / $(TOTAL_FILES) ))" "$<"
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@

	


#include dependencies
-include $(DEPS)

debug: CLFAGS += -g
debug: re

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft
	@rm -rf $(LIBMLX)/build
	@printf "$(GREEN)✓ Clean complete$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)✓ Full clean complete$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re debug libft42 check_dependencies check_submodules doc
