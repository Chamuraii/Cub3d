/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/18 17:41:43 by jchamak          ###   ########.fr       */
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
	int		i;
	int		end;
	int		wide;

	//dist = dist * fabs(sin((rad + 180) * PI / 180)) * fabs(cos((rad + 180) * PI / 180));
	end = (HEIGHT - dist * HEIGHT / 50);
	i = HEIGHT - end;
	rad = good_angles(all, rad);
	wide = rad * WIDTH / FOV;
	if (rad == 0)
		wide = WIDTH + 1;
	i += 2;
//	printf ("drawing a line from %d to %d, for %f m at %f degres (x = %d)\n", i, end, dist, rad, wide);
	while (i <= end && i > 0)
		mlx_put_pixel(all->background, -wide, i ++, 0xff0000);
//	printf("i = %d\n", i);
}

double	cadran(t_all *all, double rad)
{
	double	a;

	if (rad > 1 && rad < 90)
	{
		a = 1 / tan(rad * PI / 180);
	//	printf ("cad 1\n");
	}
	else if (rad > 90 && rad < 179)
	{
		a = -1 / tan(rad * PI / 180);
	//	printf ("cad 2\n");
	}
	else if (rad > 181 && rad <= 270)
	{
		a = 1 / tan(rad * PI / 180);
	//	printf ("cad 3\n");
	}
	else if (rad > 270 && rad < 359)
	{
		a = -1 / tan(rad * PI / 180);
	//	printf ("cad 4\n");
	}
	else
		a = 100;
	//printf("a = %f\n", a);
	return (a);
}

double	change_x(t_all *all, double rad, double a, double x)
{
	rad = good_angles(all, rad + all->z);
	if (a > 1)
		a = 1 / a;
	if (rad <= 135 && rad > 45)
		x -= a;
	else if (rad <= 225 && rad > 135)
		x += a;
	else if (rad < 315 && rad > 225)
		x += a;
	else
		x -= a;
	//printf("x = %f", x);
	return (x);
}

double	change_y(t_all *all, double rad, double a, double y)
{
	rad = good_angles(all, rad + all->z);
	if (a > 1)
		a = 1 / a;
	if (rad < 135 && rad > 45)
		y += a;
	else if (rad < 225 && rad > 135)
		y += a;
	else if (rad < 315 && rad > 225)
		y -= a;
	else
		y -= a;
	//printf("  y = %f\n", y);
	return (y);
}

void	to_ray_minimap(t_all *all, double x, double y, double a, int i, double rad)
{
//	printf("x = %f, y = %f\n", x, y);
//	printf("rad = %f\n", rad);
	all->ray_hits[i][0] = (y / a + all->y);
	all->ray_hits[i][1] = x + all->x;
	////printf("ray to (%f %f)\n", all->ray_hits[i][1], all->ray_hits[i][0]);
	//if (rad < 315 && rad > 225)
	//{
	//	all->ray_hits[i][0] = floor(y / a + all->y);
		//all->ray_hits[i][1] = (x + all->x);
		//printf("modified ray to (%f %f)\n", all->ray_hits[i][1], all->ray_hits[i][0]);
	//}
/* 	if (all->ray_hits[i][0] == all->y && all->ray_hits[i][1] == all->x)
	{
		printf("ahhhhh\n");
		draw_pixel_line(all, 0, rad);
	} */
	//	printf("checking (%d, %f) %f//\n", (int)(x + all->x), y / a + all->y, y + all->y);
	//	printf("so.... %d\n", all->map[(int)floor(y / a + all->y)][(int)floor(x + all->x)]);
}

double	distance(t_all *all, double x, double y, double a, double rad)
{
	double	n;
	double	m;

	//printf("-- %f -> %f\n", all->z - rad, cos(rad * PI / 180));
	n = sqrt(pow(x, 2) + pow(y / a, 2));
	n *= (cos((all->z - rad) * PI / 180));
/* 	if (rad > 225 || rad < 45)
	else
		n *= fabs(cos(rad * PI / 180)); */
	//n *= sqrt(pow(fabs(sin((rad + 180) * PI / 180)), 2) + pow(fabs(cos((rad + 180) * PI / 180)), 2));
//	m = sqrt(pow(x * cos((rad) * PI / 180), 2) + pow((y / a) * sin((rad) * PI / 180), 2));
//	printf("ddd %f\n", n * sqrt(pow(x * cos((rad) * PI / 180), 2) + pow((y / a) * sin((rad) * PI / 180), 2)));
	return (n);
//	return (sqrt(pow(x * fabs(cos(rad * PI / 180)), 2) + pow((y / a) * fabs(sin(rad * PI / 180)), 2)));
}

void	every_ray(t_all *all, double rad)
{
	double	x;
	double	y;
	double	dist;
	double	a;
	int		i;

	rad = 0;
	i = 0;
	while (rad <= FOV)
	{
		x = 0;
		y = 0;
		a = cadran (all, good_angles(all, rad + all->lz));
		if (good_angles(all, rad + all->lz) == 180 || good_angles(all, rad + all->lz) == 0)
		{
			while (x + all->x <= all->map_width && x + all->x >= 0
				&& !(all->map[(int)(y / a + all->y + 1e-9)][(int)(x + all->x + 1e-9)] == 1))
			{
				to_ray_minimap(all, x, 0, a, i, good_angles(all, rad + all->lz));
				x = change_x(all, rad + 45 - FOV / 2, a, x);
				dist = fabs(x);
			}
			i ++;
		}
		else if (good_angles(all, rad + all->lz) == 90 /* || good_angles(all, rad + all->lz) == 270 */)
		{
			while (y + all->y <= all->map_height && y + all->y >= 0
				&& !(all->map[(int)(y + all->y + 1e-9)][(int)(x + all->x + 1e-9)] == 1))
			{
				to_ray_minimap(all, 0, y, 1, i, good_angles(all, rad + all->lz));
				y ++;
				dist = fabs(y);
			}
			i ++;
		}
		else
		{
			while (x + all->x <= all->map_width && y / a + all->y
				<= all->map_height && x + all->x >= 0 && y / a + all->y >= 0
				&& (all->map[(int)(y / a + all->y + 1e-9)][(int)(x + all->x + 1e-9)] != 1))
				/*  || (x + a + all->x > ceil(x + all->x) && all->map[(int)
						(y / a + all->y + 1e-9)][(int)ceil(x + all->x)] == 1) */
			{
				to_ray_minimap(all, x, y, a, i, good_angles(all, rad + all->lz));
			//	printf("4x == %f, y / a == %f\n", x, y / a);
	//			printf("x == %d, y / a == %d\n", (int)(x + all->x + 1e-9), (int)(y / a + all->y + 1e-9));
				dist = distance(all, x, y, a, rad + all->lz);
				x = change_x(all, rad + 45 - FOV / 2, a, x);
			//	printf("       new x = %f -- %f\n", x, ceil(all->x) - all->x);
	//			printf("       new x = %f\n", x);
				y = change_y(all, rad + 45 - FOV / 2, a, y);
				//printf("hmmm checking (%d, %d) //... %f\n", (int)(x + all->x + 1e-9), (int)(y / a + all->y + 1e-9), all->lz + rad);
			}
			i ++;
		}
		//printf("dist = %f\n", dist);
	//	printf("x = %f / a = %f / rad = %f\n", x, a, rad);
		draw_pixel_line(all, dist, good_angles(all, rad));
	//	printf("***%f, %f [y %f, a %f] ----- (%d, %d) so : %d\n", x, y / a, y, a, (int)(x + all->x + 1e-9), (int)(y / a + all->y + 1e-9), all->map[(int)(y / a + all->y + 1e-9)][(int)(x + all->x + 1e-9)]);
	//	printf("rad = %f\n", rad + all->lz);
		//rad += 1;
		rad += 0.04;
		all->ray_hits[i][0] = -1;
		all->ray_hits[i][1] = -1;
	}
}

void	camera_turn(t_all *all, int i)
{
	all->z = good_angles(all, all->z + 5 * i);
	all->hz = good_angles(all, all->z + FOV / 2);
	all->lz = good_angles(all, all->z - FOV / 2);
}

void	ray(t_all *all)
{
	sky_floor(all);
	every_ray(all, all->lz);
	draw_minimap(all);
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
	printf("%f, %f!!\n", all->x, all->y);
	ray(all);
	return (1);
}

void	my_hook(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
//	all->g_img = mlx_texture_to_image(all->mlx, all->texture); // segfault
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
	//mlx_set_setting(MLX_STRETCH_IMAGE, 1);
//	all.texture = mlx_load_png("grass.png"); // segfault
//	all.g_img = mlx_texture_to_image(all.mlx, all.texture); // segfault
	ray(&all);
//	printf ("starting at (%f, %f)\n", all.x, all.y);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (0);
}
