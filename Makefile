# Nombre del programa
NAME       = Cub3d
# Flags de compilacion
FLAGS      = -Wall -Wextra -Werror -g
# Directorios
SRC_DIR    = ./src/
OBJ_DIR    = ./obj/
INC_DIR    = ./include/
LIBFT_DIR  = ./libft/
MLX_DIR    = ./MLX42/
# Archivos fuentes y objetos
SRC_FILES  =	animation.c \
				exit.c \
				flood_fill.c \
				get_lines.c \
				get_rgba.c \
				hooks.c \
				init.c \
				main.c \
				map_validator.c \
				minimap.c \
				minimap_fov.c \
				minimap_main.c \
				move.c \
				paint.c \
				parser_main.c \
				rays.c \
				rgb_check.c \
				sprites.c \
				texture_parser.c \
				textures.c

OBJ_FILES  = $(notdir $(SRC_FILES:.c=.o))
# Direcciones
SRC        = $(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR),$(OBJ_FILES))
LIBFT      = $(addprefix $(LIBFT_DIR),libft.a)
MLX        = $(addprefix $(MLX_DIR), libmlx42.a)

BREW = "/Users/$(USER)/.brew/opt/glfw/lib/"

all: obj $(LIBFT) $(NAME)
obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $(SRC_DIR)$(notdir $<)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling..."
	@gcc $(OBJ) -lglfw -L $(BREW) -o $(NAME) $(LIBFT) $(MLX)
	@echo "\033[0m$(NAME) \033[0;32mgenerated!"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[0;31mCleaning"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(NAME) removed!\033[0m"

re: fclean all

.PHONY: all clean fclean re