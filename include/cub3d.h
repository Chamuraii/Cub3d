/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:25:42 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/01 15:01:12 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include "../libft/libft.h"

# define PI 3.14159265358979323846
# define HEIGHT 700
# define WIDTH 1200

typedef struct s_all
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	mlx_image_t		*background;
	mlx_texture_t	*texture;
	double			x;
	double			y;
	double			z;
	double			hz;
	double			lz;
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
}			t_all;

int		main_validator(t_all *all, char **argv);
void	parser_init(t_all *all);
void	ft_free(t_all *all);

#endif