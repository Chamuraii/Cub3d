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
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

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
	int				gun_bool;
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
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	double			texture_x;
	double			range;
	double			texture_range;
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
	char			*next_line;
	int				is_there_map;
	double			h;
	double			w;
	double			m;
	double			n;
	int				a;
	int				b;
	int				player_count;
	int				mouse_counter;
	int32_t			mouse_x_pos;
	int32_t			mouse_y_pos;
	uint32_t		mouse_flag;
}			t_all;

// main.c

void			ft_exit(t_all *all, int status);
int				main(int argc, char **argv);

// move.c

double			good_angles(double ang);
int				diag_jump(t_all *all, int x, int y);
void			move_player(t_all *all, double x, double y);
void			my_hook(void *param);

// paint.c

void			draw_pixel_line(t_all *all, double dist);
void			what_side(t_all *all, double rad);

// rays.c

int				is_wall_h(t_all *all, int rad, double x, double y);
int				is_wall_v(t_all *all, int rad, double x, double y);
void			cast(t_all *all, double rad, int o);
void			rays(t_all *all);
void			final(t_all *all, int i);

void			my_key_hook(struct mlx_key_data keydata, void *param);
void			mouse(t_all *all);
void			paint_map(t_all *all, int offset_x,
					int offset_y, unsigned int color);
void			paint_map_player(t_all *all, int offset_x, int offset_y);
void			minimap_init_y(t_all *all, int *offset_y, int *y_off_u);
void			minimap_init_x(t_all *all, int *off_x,
					int *x_off_l, int *player_dist);
void			draw_minimap_2(t_all *all, int y_off_u,
					int x_off_l, int player_dist);
void			draw_minimap(t_all *all);
void			update_player_pos(t_all *all);
int				get_sum(double x, double ray);
void			draw_fov(t_all *all, int start_y, int start_x, int i);
void			draw_ray_minimap(t_all *all, int start_y, int start_x);
void			parser_init_2(t_all *all);
void			parser_init(t_all *all);
void			parser_setter(t_all *all);
char			*get_next_line_no_nl(int fd);
void			texture_map_check(t_all *all, int step, char *str, int j);
int				texture_map_validator(t_all *all, char *str, int step);
int				rgb_repeated_checker(t_all *all, int boole);
int				rgb_validate_coma(char *str, int *comma_counter, int i);
void			rgb_validator(t_all *all, char *str, int boole);
int				cub_directions_validator(t_all *all, char *str);
char			**map_copy(t_all *all, char ***matrix, int height);
void			flood_fill(t_all *all, char **map, int y, int x);
int				flood_validator(t_all *all, char **map);
void			map_validator_2(t_all *all, char **str, int i);
void			map_validator_3(t_all *all, char ***matrix, int i, int j);
void			set_player(t_all *all, char **str, int i, int j);
char			*get_line_map(char ***matrix, char **str, int fd, int *j);
int				map_validator(t_all *all, char **str, int fd);
int				cub_line_validator(t_all *all, char **str, int fd);
int				cub_validator(t_all *all, char **argv, int fd, char **str);
void			parse_map(t_all *all);
int				main_validator(t_all *all, char **argv, int argc);
int				get_textures(t_all *all);
unsigned int	get_rgba(int r, int g, int b, int a);
unsigned int	get_rgb(mlx_texture_t *side, uint32_t y, double x);
unsigned int	get_pixel_color(t_all *all, double scale_y, double y);
void			start_gun(t_all *all);
void			gun1(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun2(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun3(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun4(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun5(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun6(t_all *all, uint32_t *up, uint32_t *down, int *counter);
void			gun(t_all *all);

#endif
