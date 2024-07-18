# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 09:44:16 by ysmeding          #+#    #+#              #
#    Updated: 2023/10/16 13:55:39 by jchamak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

CC = clang

CFLAGS = -Wall -Wextra -Werror -O3

LIBFT = ./libft/libft.a

MLX = ./MLX42/libmlx42.a
MLX_DIR = ./MLX42

BREW = -I include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRC_DIR = src

OBJ_DIR = obj

LIBFT_DIR  = ./libft/

SRC_BONUS_DIR = src_bonus

OBJ_BONUS_DIR = obj_bonus

SRC_FILES = 	src/exit.c \
                src/flood_fill.c \
                src/get_lines.c \
                src/get_rgba.c \
                src/init.c \
                src/main.c \
                src/map_validator.c \
                src/move.c \
                src/paint.c \
                src/parser_main.c \
                src/rays.c \
                src/rgb_check.c \
                src/texture.c \

SRC_BONUS =	src_bonus/animation_bonus.c \
               		src_bonus/exit_bonus.c \
                	src_bonus/flood_fill_bonus.c \
                	src_bonus/get_lines_bonus.c \
               		src_bonus/get_rgba_bonus.c \
                	src_bonus/hooks_bonus.c \
                	src_bonus/init_bonus.c \
                	src_bonus/main_bonus.c \
                	src_bonus/map_validator_bonus.c \
                	src_bonus/minimap_bonus.c \
                	src_bonus/minimap_fov_bonus.c \
                	src_bonus/minimap_main_bonus.c \
                	src_bonus/move_bonus.c \
                	src_bonus/paint_bonus.c \
                	src_bonus/parser_main_bonus.c \
                	src_bonus/rays_bonus.c \
                	src_bonus/rgb_check_bonus.c \
                	src_bonus/sprites_bonus.c \
                	src_bonus/texture_bonus.c \

OBJ_FILES = $(SRC_FILES:src/%.c=obj/%.o)

OBJ_BONUS_FILES = $(SRC_BONUS:src_bonus/%.c=obj_bonus/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_FILES)
	@echo "\033[0;32mCompiling..."
	@ $(CC) -lm $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME) $(MLX) $(BREW)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJ_BONUS_FILES)
	@echo "\033[0;32mBonus compiling..."
	@ $(CC) $(shell pkg-config --libs glfw3) -lm $(CFLAGS) $(OBJ_BONUS_FILES) $(LIBFT) -o $(NAME_BONUS) $(MLX) $(BREW)

$(LIBFT):
	@ make -C $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(shell pkg-config --cflags glfw3) $(CFLAGS) -c -o $@ $<

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(MLX):
	@ make -C $(MLX_DIR)

clean:
	@echo "\033[0;31mCleaning..."
	@ rm -rf $(OBJ_DIR)
	@ rm -rf $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(NAME) removed!\033[0m"
	@ rm -rf $(NAME)
	@ rm -rf $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: re clean fclean all bonus