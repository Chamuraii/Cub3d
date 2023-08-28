# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 11:24:07 by jchamak           #+#    #+#              #
#    Updated: 2023/08/28 12:06:37 by jchamak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d

MLX42 =  MLX42/libmlx42.a

MLXINC = -lglfw -L /Users/jchamak/.brew/opt/glfw/lib/

INC = -I include -I MLX42/include/MLX42

LIBFT = libft/libft.a

SRC =	main.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra #-Werror

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX42)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLXINC) -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(INC) -c $(SRC)

$(LIBFT):
	make -C libft

$(MLX42):
	make -C MLX42

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all