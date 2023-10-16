# Nombre del programa
NAME       = cub3D
# Flags de compilacion
FLAGS      = -Wall -Wextra -Werror
# Directorios
SRC_DIR    = ./src/
SRC_BONUS  = ./src_bonus/
OBJ_DIR    = ./obj/
INC_DIR    = ./include/
LIBFT_DIR  = ./libft/
MLX_DIR    = ./MLX42/
# Archivos fuentes y objetos
SRCS_FILES = 	animation.c \
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

SRCS_BONUS = 	animation_bonus.c \
				exit_bonus.c \
				flood_fill_bonus.c \
				get_lines_bonus.c \
				get_rgba_bonus.c \
				hooks_bonus.c \
				init_bonus.c \
				main_bonus.c \
				map_validator_bonus.c \
				minimap_bonus.c \
				minimap_fov_bonus.c \
				minimap_main_bonus.c \
				move_bonus.c \
				paint_bonus.c \
				parser_main_bonus.c \
				rays_bonus.c \
				rgb_check_bonus.c \
				sprites_bonus.c \
				texture_parser_bonus.c \
				textures_bonus.c

OBJ_FILES  = $(notdir $(SRC_FILES:.c=.o))
OBJ_BONUS  = $(notdir $(SRC_BONUS:.c=.o))
SRC        = $(addprefix $(SRC_DIR),$(SRC_FILES))
SRCB        = $(addprefix $(SRC_BONUS),$(SRC_BONUS))
OBJ        = $(addprefix $(OBJ_DIR),$(OBJ_FILES))
OBJB        = $(addprefix $(OBJ_DIR),$(OBJ_BONUS))
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

bonus : $(OBJB)
	@echo "\033[0;32mBonus compiling..."
	@gcc $(OBJB) -lglfw -L $(BREW) -o $(NAME) $(LIBFT) $(MLX)
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