/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:25:42 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/29 14:05:17 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"
# include "libft/libft.h"

# define PI 3.14159265

typedef struct s_all
{
	mlx_t				*mlx;
	mlx_image_t			*g_img;
	mlx_image_t			*background;
	mlx_texture_t		*texture;
	double				x;
	double				y;
	int					z;
	int					hz;
	int					lz;
}			t_all;

#endif