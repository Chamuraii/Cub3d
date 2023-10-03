/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/27 16:27:34 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// pb of corner if round player coordinates (top left corner disappears)
// really rare go through diagonal ray in middle of corner

void	sky_floor(t_all *all);

void	ft_exit(char *reason, int status)
{
	ft_printf("%s\n", reason);
	exit(status);
}

double	good_angles(t_all *all, double ang)
{
	while (ang >= 360)
		ang -= 360;
	while (ang < 0)
		ang += 360;
	return (ang);
}

void	draw_pixel_line(t_all *all, double dist, double rad)
{
	double		i;
	int			start;
	int			end;
	int			wide;

	if (dist < 1)
		i = 1;
	else
		i = 1 / dist;
	start = (HEIGHT - HEIGHT * i) / 2;
	rad = good_angles(all, rad);
	wide = rad * WIDTH / FOV;
	if (rad == 0)
		wide = -WIDTH + 1;
	start ++;
	end = HEIGHT - start;
	while (start <= end && start > 0)
	{
		mlx_put_pixel(all->background, -wide - 1, start, get_pixel_color(all, start, (double)((end - ((HEIGHT - HEIGHT * i) / 2))), end));
		++start;
	}
	all->ray_num++;
}

int	is_wall_h(t_all *all, int rad, double x, double y)
{
	if (rad > 180)
		y -= 1e-9;
	if (y <= 0 || y >= all->map_height || x <= 0 || x >= all->map_width
		|| all->map[(int)y][(int)x] == 1)
	{
		all->finaly[1] = y;
		all->finalx[1] = x;
		all->dist[1] = sqrt(pow(x - all->x, 2) + pow(y - all->y, 2))
			* (cos((all->z - rad) * PI / 180));
		return (1);
	}
	return (0);
}

int	is_wall_v(t_all *all, int rad, double x, double y)
{
	if (rad > 270 || rad < 90)
		x -= 1e-9;
	if (y <= 0 || y >= all->map_height || x <= 0 || x >= all->map_width
		|| all->map[(int)y][(int)x] == 1)
	{
		all->finaly[2] = y;
		all->finalx[2] = x;
		all->dist[2] = sqrt(pow(x - all->x, 2) + pow(y - all->y, 2))
			* (cos((all->z - rad) * PI / 180));
		return (1);
	}
	return (0);
}

void	ver(t_all *all, double rad)
{
	double	x;
	double	y;
	int		o;

	o = 0;
	while (1)
	{
		if (rad == 0 || rad == 90 || rad == 180 || rad == 270)
			rad += 0.2;
		x = floor(all->x - o);
		if (rad < 270 && rad > 90)
			x = ceil(all->x + o);
		y = all->y - tan(good_angles(all, rad - 180) * PI / 180) * (x - all->x);
		o ++;
		if (is_wall_v(all, rad, x, y) || y > all->map_height)
			break ;
	}
}

void	hor(t_all *all, double rad)
{
	double	x;
	double	y;
	int		o;

	o = 0;
	while (1)
	{
		if (rad == 0 || rad == 90 || rad == 180 || rad == 270)
			rad += 0.2;
		y = floor(all->y - o);
		if (rad < 180)
			y = ceil(all->y + o);
		x = all->x + tan(good_angles(all, rad - 90) * PI / 180) * (y - all->y);
		o ++;
		if (is_wall_h(all, rad, x, y) || x > all->map_width)
			break ;
	}
}

void	final(t_all *all, int i)
{
	all->dist[0] = all->dist[1];
	all->finalx[0] = all->finalx[1];
	all->finaly[0] = all->finaly[1];
	all->dir = 0;
	if (all->dist[1] > all->dist[2])
	{
		all->dist[0] = all->dist[2];
		all->finalx[0] = all->finalx[2];
		all->finaly[0] = all->finaly[2];
		all->dir = 1;
	}
	all->ray_hits[i][0] = all->finaly[0];
	all->ray_hits[i][1] = all->finalx[0];
	if (all->ray_hits[i][0] < 0)
		all->ray_hits[i][0] = 0;
	if (all->ray_hits[i][1] < 0)
		all->ray_hits[i][1] = 0;
	if (all->ray_hits[i][0] >= all->map_height)
		all->ray_hits[i][0] = all->map_height - 0.1;
	if (all->ray_hits[i][1] >= all->map_width)
		all->ray_hits[i][1] = all->map_width - 0.1;
}

void	rays(t_all *all)
{
	double	rad;
	int		i;

	rad = 0;
	i = 0;
	sky_floor(all);
	while (rad <= FOV)
	{
		hor(all, good_angles(all, rad + all->z - FOV / 2));
		ver(all, good_angles(all, rad + all->z - FOV / 2));
		final(all, i);
		i++;
		all->ray_hits[i][0] = -1;
		all->ray_hits[i][1] = -1;
		draw_pixel_line(all, all->dist[0], good_angles(all, rad));
		rad += 0.042;
	}
	all->ray_hits[i][0] = -1;
	all->ray_hits[i][1] = -1;
	draw_minimap(all);
}

int	diag_jump(t_all *all, int x, int y)
{
	x -= (int)all->x;
	y -= (int)all->y;
	if ((x == 1 && y == 1 || x == -1 && y == -1)
		&& all->map[(int)all->y][(int)all->x + x] == 1
		&& all->map[(int)all->y + y][(int)all->x] == 1)
		return (0);
	if ((x == -1 && y == 1 || x == 1 && y == -1)
		&& all->map[(int)all->y][(int)all->x + x] == 1
		&& all->map[(int)all->y - y][(int)all->x] == 1)
		return (0);
	return (1);
}

void	move_player(t_all *all, double x, double y)
{
	if (all->map[(int)floor(all->y + y)][(int)floor(all->x + x)] != 1
		&& diag_jump(all, all->x + x, all->y + y))
	{
		all->x += x;
		all->y += y;
	}
}

void	my_hook(void *param)
{
	t_all	*all;
	static int counter;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE)) {
		ft_exit("BYE <3", 1);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W)) {
		move_player(all, (-cos(all->z * PI / 180)) / 30, (sin(all->z * PI / 180)) / 30);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S)) {
		move_player(all, (cos(all->z * PI / 180)) / 30, (-sin(all->z * PI / 180)) / 30);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A)) {
		move_player(all, (cos((all->z - 90) * PI / 180)) / 30,
					(-sin((all->z - 90) * PI / 180)) / 30);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D)) {
		move_player(all, (cos((all->z + 90) * PI / 180)) / 30,
					(-sin((all->z + 90) * PI / 180)) / 30);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT)) {
		all->z = good_angles(all, all->z - CAM_SPEED);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT)) {
		all->z = good_angles(all, all->z + CAM_SPEED);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_L)) {
		if (!all->mouse_flag) {
			all->mouse_flag = 1;
		} else {
			all->mouse_flag = 0;
		}
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_HIDDEN);
	}
	if (all->mouse_flag)
	{
		if (counter == 2)
		{
			mlx_set_mouse_pos( all->mlx, WIDTH / 2, HEIGHT / 2);
			counter = 0;
		}
		++counter;
		mlx_get_mouse_pos( all->mlx, &(all->mouse_x_pos), &(all->mouse_y_pos));
		all->z = good_angles(all, all->z - ((all->mouse_x_pos - (WIDTH / 2)) / 10));
	}
	if (mlx_is_mouse_down(all->mlx, MLX_MOUSE_BUTTON_LEFT))
		all->gun_bool = 1;
	if (all->gun_bool)
	{
		gun(all);
	}
	rays(all);
}

void	sky_floor(t_all *all)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (y ++ < HEIGHT / 2 - 1)
	{
		while (x ++ < WIDTH)
			mlx_put_pixel(all->background, x, y, 0x8989ff);
		x = -1;
	}
	y = HEIGHT / 2 - 1;
	while (y ++ < HEIGHT - 1)
	{
		while (x ++ < WIDTH)
			mlx_put_pixel(all->background, x, y, 0xff9e3d);
		x = -1;
	}
}

int	main(int argc, char **argv)
{
	t_all	all;

	parser_init(&all);
	if (!main_validator(&all, argv, argc))
		return (ft_printf ("Error\n"), -1);
	ft_printf ("Map validation successful!\n");
	if (!get_textures(&all))
		return (ft_printf ("Error\n"), -1);
	else
		ft_printf ("Texture validation successful!\n");
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	if (!all.mlx)
		ft_exit("error\n-MLX PROBLEM-", -1);
	mlx_set_window_title(all.mlx, "Cub3d");
	all.background = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	rays(&all);
	start_gun(&all);
	mlx_loop_hook(all.mlx, my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (0);
}