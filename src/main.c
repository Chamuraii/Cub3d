/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/26 15:37:58 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

	i = 1 / dist;
	if (i > 1)
		i = 1;
	start = (HEIGHT - HEIGHT * i) / 2;
	rad = good_angles(all, rad);
	wide = rad * WIDTH / FOV;
	if (rad == 0)
		wide = -WIDTH + 1;
	start += 2;
	end = HEIGHT - start;
	//printf ("drawing a line from %d to %d, for %f m at %f degres (x = %d)\n", start, end, dist, rad, wide);
	while (start <= end && start > 0)
		mlx_put_pixel(all->background, -wide - 1, start ++, 0xff0000);
}

int	is_wall_h(t_all *all, int rad, double x, double y)
{
	if (rad > 180)
		y -= 1e-9;
	if (y <= 0 || y >= all->map_height || x <= 0 || x >= all->map_width
		|| all->map[(int)y][(int)x] == 1)
	{
		all->finalyh = y;
		all->finalxh = x;
		all->disth = sqrt(pow(x - all->x, 2) + pow(y - all->y, 2))
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
		all->finalyv = y;
		all->finalxv = x;
		all->distv = sqrt(pow(x - all->x, 2) + pow(y - all->y, 2))
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
	all->dist = all->disth;
	all->finalx = all->finalxh;
	all->finaly = all->finalyh;
	all->dir = 0;
	if (all->disth > all->distv)
	{
		all->dist = all->distv;
		all->finalx = all->finalxv;
		all->finaly = all->finalyv;
		all->dir = 1;
	}
	all->ray_hits[i][0] = all->finaly;
	all->ray_hits[i][1] = all->finalx;
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
		hor(all, good_angles(all, rad + all->lz));
		ver(all, good_angles(all, rad + all->lz));
		final(all, i ++);
		draw_pixel_line(all, all->dist, good_angles(all, rad));
		rad += 0.04;
	}
	all->ray_hits[i][0] = -1;
	all->ray_hits[i][1] = -1;
	draw_minimap(all);
}

void	camera_turn(t_all *all, int i)
{
	all->z = good_angles(all, all->z + CAM_SPEED * i);
	all->hz = good_angles(all, all->z + FOV / 2);
	all->lz = good_angles(all, all->z - FOV / 2);
}

int	press_keys(mlx_key_data_t keydata, t_all *all)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_W)
		&& all->map[(int)floor(all->y + (sin(all->z * PI / 180)))]
		[(int)floor(all->x - (cos(all->z * PI / 180)))] != 1)
	{
		all->x -= cos(all->z * PI / 180);
		all->y += sin(all->z * PI / 180);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S)
		&& all->map[(int)floor(all->y - (sin(all->z * PI / 180)))]
		[(int)floor(all->x + (cos(all->z * PI / 180)))] != 1)
	{
		all->x += cos(all->z * PI / 180);
		all->y -= sin(all->z * PI / 180);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A)
		&& all->map[(int)floor(all->y - (sin((all->z - 90) * PI / 180)))]
		[(int)floor(all->x + (cos((all->z - 90) * PI / 180)))] != 1)
	{
		all->x += cos((all->z - 90) * PI / 180);
		all->y -= sin((all->z - 90) * PI / 180);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D)
		&& all->map[(int)floor(all->y - (sin((all->z + 90) * PI / 180)))]
		[(int)floor(all->x + (cos((all->z + 90) * PI / 180)))] != 1)
	{
		all->x += cos((all->z + 90) * PI / 180);
		all->y -= sin((all->z + 90) * PI / 180);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		camera_turn(all, -1);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		camera_turn(all, 1);
	else
		return (0);
	rays(all);
	return (1);
}

void	my_hook(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		ft_exit("BYE <3", 1);
	press_keys(keydata, all);
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
	else
		ft_printf ("Map validation successful!\n");
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	if (all.mlx)
		mlx_set_window_title(all.mlx, "Cub3d");
	else
		ft_exit("error\n-MLX PROBLEM-", -1);
	all.background = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	all.z = START_ANGLE;
	all.lz = START_ANGLE - FOV / 2;
	all.hz = START_ANGLE + FOV / 2;
	rays(&all);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (0);
}
