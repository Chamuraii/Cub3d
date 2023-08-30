# Nombre del programa
NAME       = Cub3d
# Flags de compilacion
FLAGS      = -g
# Directorios
SRC_DIR    = ./src/
OBJ_DIR    = ./obj/
INC_DIR    = ./include/
LIBFT_DIR  = ./libft/
MLX_DIR    = ./MLX42/
# Archivos fuentes y objetos
SRC_FILES  = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES  = $(notdir $(SRC_FILES:.c=.o))
# Direcciones
SRC        = $(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR),$(OBJ_FILES))
LIBFT      = $(addprefix $(LIBFT_DIR),libft.a)
MLX        = $(addprefix $(MLX_DIR), libmlx42.a)

BREW = "/Users/$(USER)/.brew/opt/glfw/lib/"

# Se compila el archivo binario (ejecutable).
all: obj $(LIBFT) $(NAME)
# Crea la carpeta donde estará los objetos.
obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $(SRC_DIR)$(notdir $<)
# Compila la biblioteca libft.a
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)
# Se compila los objetos con las librerías y archivos
$(NAME): $(OBJ)
	@echo "(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compilando, espere unos segundos..."
	@gcc $(OBJ) -lglfw -L $(BREW) -o $(NAME) $(LIBFT) $(MLX)
	@echo "(•̀ᴗ•́)و $(NAME) generado!"
# Remueve todos los archivos objetos
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "¯\_(ツ)_/¯ Objetos removidos!"
# Remueve todos los archivos objetos, binarios y sus respectivas carpetas
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "(╯°□°）╯︵ ┻━┻ $(NAME) removido!"
# Hace un re-make (como si se hubiera ejecutado Make por primera vez)
re: fclean all
# Le dice al make que estos nombres no son archivos
.PHONY: all clean fclean re