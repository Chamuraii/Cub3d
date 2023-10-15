/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:25:42 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/13 21:00:28 by jchamak          ###   ########.fr       */
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
# include <GLFW/glfw3.h>

# define PI 3.14159265358979323846
# define HEIGHT 700
# define WIDTH 1050
# define FOV 45
# define CAM_SPEED 1.5
# define SPEED 1

typedef struct s_all
{
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	mlx_image_t		*background;
	mlx_image_t		*gun_img;
	mlx_texture_t	*gun;
	int 			gun_bool;
	mlx_texture_t	*texture;
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*side;
	double			x;
	double			y;
	double			z;
	double			oldx;
	double			oldy;
	int				oldchar;
	double			ray_hits[88000][2];
	unsigned int	ray_num;
	double			dist[3];
	double			finalx[3];
	double			finaly[3];
	int				dir;
	char			*NO_texture;
	char			*SO_texture;
	char			*WE_texture;
	char			*EA_texture;
	int				floor_color_rgb[4];
	int				ceiling_color_rgb[4];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	unsigned int	map_width;
	unsigned int	map_height;
	char			**map_char;
	char			**map_cpy;
	int				**map;
	unsigned int	texture_counter;
	char	*next_line;
	int 	is_there_map;
	double		h;
	double		w;
	double		m;
	double 		n;
	int			a;
	int 		b;

	int 		mouse_counter;
	int32_t	mouse_x_pos;
	int32_t	mouse_y_pos;
	uint32_t	mouse_flag;
}			t_all;

int		main_validator(t_all *all, char **argv, int argc);
void	parser_init(t_all *all);
void	ft_free(t_all *all);
void	draw_minimap(t_all *all);
unsigned int		get_pixel_color(t_all *all, double range);
int					get_textures(t_all *all);
void				gun(t_all *all);
unsigned int get_rgba_img(uint8_t *pixels, unsigned int width, unsigned int y, double x);
void	start_gun(t_all *all);
unsigned int	get_rgba(int r, int g, int b, int a);
void	mouse(t_all *all);

// main.c

void	ft_exit(t_all *all, int status);
int		main(int argc, char **argv);

// move.c

double	good_angles(double ang);
int		diag_jump(t_all *all, int x, int y);
void	move_player(t_all *all, double x, double y);
void	my_hook(void *param);

// paint.c

void	background(t_all *all);
void	draw_pixel_line(t_all *all, double dist, double rad);
void	what_side(t_all *all, double rad);

// rays.c

int		is_wall_h(t_all *all, int rad, double x, double y);
int		is_wall_v(t_all *all, int rad, double x, double y);
void	cast(t_all *all, double rad, int o);
void	rays(t_all *all);
void	final(t_all *all, int i);

#endif
