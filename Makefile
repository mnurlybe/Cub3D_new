NAME = cub3D

SRC_DIR = src
# BONUS_DIR = bonus
LIBMLX = ./MLX42
MXL = MLX42/build/libmlx42.a

# Recursively find all .c files in SRC_DIR and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

CFLAGS = -Wall -Wextra -Werror
#FSANITIZE = -g3 -fsanitize=address
LIBFLAGS = -L./libft -lft -lm
MLXFLAGS = -Iinclude -ldl -lglfw -pthread
MY_HEADER = ./includes/

OBJ_DIR = obj

all:  libft42 $(NAME)

libft42:
	make -C libft
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:$(SRC_DIR)/%.c=%.o))
DEPS = $(OBJECTS:.o=.d)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@
	@echo -n "Compiling src... $<\r"

$(NAME): $(OBJECTS)
	@gcc $(CFLAGS) -MMD -o $(NAME) $(OBJECTS) $(MXL) $(LIBFLAGS) $(MLXFLAGS)

#include dependencies
-include $(DEPS)

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJECTS))

debug: CLFAGS += -g
debug: re

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
