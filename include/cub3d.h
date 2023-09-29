/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:25:42 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/27 16:11:42 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <GLFW/glfw3.h>

# define PI 3.14159265358979323846
# define HEIGHT 700
# define WIDTH 1050
# define FOV 45
# define START_ANGLE 270
# define CAM_SPEED 1.5

typedef struct s_all
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	mlx_image_t		*background;
	mlx_texture_t	*texture;
	double			x;
	double			y;
	double			z;
	double			oldx;
	double			oldy;
	int				oldchar;
	double			ray_hits[2000][2];
	double			dist[3];
	double			finalx[3];
	double			finaly[3];
	int				dir;
	char			*NO_texture;
	char			*SO_texture;
	char			*WE_texture;
	char			*EA_texture;
	int				floor_color[4]; // 3 spaces for RGB values and 1 bool for already parsed
	int				ceiling_color[4];
	unsigned int	map_width;
	unsigned int	map_height;
	char			**map_char;
	char			**map_cpy;
	int				**map;
	unsigned int	i;
	unsigned int	j;

	int32_t	mouse_x_pos;
	int32_t	mouse_y_pos;
	uint32_t	mouse_flag;
}			t_all;

int		main_validator(t_all *all, char **argv, int argc);
void	parser_init(t_all *all);
void	ft_free(t_all *all);
void	draw_minimap(t_all *all);

#endif