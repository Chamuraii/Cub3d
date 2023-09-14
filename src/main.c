/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/14 16:34:19 by jchamak          ###   ########.fr       */
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

	end = HEIGHT - dist * HEIGHT / 40;
	i = HEIGHT - end;
	rad = good_angles(all, rad);
	wide = -rad * WIDTH / 90;
	if (rad == 0)
		wide += WIDTH - 1;
	//printf ("drawing a line from %d to %d, for %f m at %f degres (x = %d)\n", i, end, dist, rad, wide);
	while (i < end && i > 0)
		mlx_put_pixel(all->background, wide, i ++, 0xff0000);
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
		a = 10;
	return (a);
}

double	change_x(t_all *all, double rad, double a, double x)
{
	if (a > 1)
		a = 1 / a;
	if (rad + all->z <= 135 && rad + all->z > 45)
		x -= a;
	else if (rad + all->z <= 225 && rad + all->z > 135)
		x += a;
	else if (rad + all->z < 315 && rad + all->z > 225)
		x += a;
	else
		x -= a;
	return (x);
}

double	change_y(t_all *all, double rad, double a, double y)
{
	if (a > 1)
		a = 1 / a;
	if (rad + all->z < 135 && rad + all->z > 45)
		y += a;
	else if (rad + all->z < 225 && rad + all->z > 135)
		y += a;
	else if (rad + all->z < 315 && rad + all->z > 225)
		y -= a;
	else
		y -= a;
	return (y);
}

void	to_ray_minimap(t_all *all, double x, double y, double a, int i)
{
	//printf("x = %f, y = %f\n", x, y);
	all->ray_hits[i][0] = y / a + all->y;
	all->ray_hits[i][1] = x + all->x;
/* 	if (x + a + all->x > ceil(x + all->x))
	{ */
	//	printf("checking (%d, %d) //\n", (int)floor(x + all->x), (int)ceil(y / a + all->y + 1e-9));
	//	printf("so.. %d\n", all->map[(int)floor(y / a + all->y + 1e-9)][(int)ceil(x + all->x)]);
// 	}
//	else
//	{
	//	all->ray_hits[i][1] = x + all->x;
	//	printf("checking (%d, %f) %d//\n", (int)(x + all->x), (y / a + all->y), (int)(y / a + all->y));
	//	printf("so.... %d\n", all->map[(int)floor(y / a + all->y)][(int)floor(x + all->x)]);
//	}
	//printf("a = %f\n", a);
}

double	distance(t_all *all, double x, double y, double a, double rad)
{
	double	n;
	double	m;

	n = sqrt(pow(x, 2) + pow(y / a, 2));
	m = sqrt(pow(x * cos((rad) * PI / 180), 2) + pow((y / a) * sin((rad) * PI / 180), 2));
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
	while (rad <= 90)
	{
		x = 0;
		y = 0;
		a = cadran (all, good_angles(all, rad + all->lz));
		if (good_angles(all, rad + all->lz) == 180 || good_angles(all, rad + all->lz) == 0)
		{
			while (x + all->x <= all->map_width && x + all->x >= 0
				&& !(all->map[(int)(y / a + all->y + 1e-9)][(int)(x + all->x + 1e-9)] == 1))
			{
				to_ray_minimap(all, x, 0, a, i);
				x = change_x(all, rad, a, x);
				dist = fabs(x);
			}
			i ++;
		}
		else if (good_angles(all, rad + all->lz) == 90 /* || good_angles(all, rad + all->lz) == 270 */)
		{
			while (y + all->y <= all->map_height && y + all->y >= 0
				&& !(all->map[(int)(y + all->y + 1e-9)][(int)(x + all->x + 1e-9)] == 1))
			{
				to_ray_minimap(all, 0, y, 1, i);
				y ++;
				dist = fabs(y);
			}
			i ++;
		}
		else
		{
			while (x + all->x <= all->map_width && y / a + all->y
				<= all->map_height && x + all->x >= 0 && y / a + all->y >= 0
				&& !(all->map[(int)(y / a + all->y + 1e-9)][(int)(x + all->x + 1e-9)]
				== 1)) /*  || (x + a + all->x > ceil(x + all->x) && all->map[(int)
						(y / a + all->y + 1e-9)][(int)ceil(x + all->x)] == 1) */
			{
				to_ray_minimap(all, x, y, a, i);
				//printf("4x == %f, y / a == %f\n", x, y/a);
				dist = distance(all, x, y, a, rad + all->lz);
				x = change_x(all, rad, a, x);
				y = change_y(all, rad, a, y);
				//printf("hmmm checking (%f, %f) //... %f\n", (x + all->x), (y / a + all->y), all->lz + rad);
			}
			i ++;
		}
		draw_pixel_line(all, dist, good_angles(all, rad));
	//	printf("rad = %f\n", rad + all->lz);
//		rad += 10;
		rad += 0.05;
		all->ray_hits[i][0] = -1;
		all->ray_hits[i][1] = -1;
	}
}

void	camera_turn(t_all *all, int i)
{
	if (i == 1)
		all->z -= 5;
	if (i == 2)
		all->z += 5;
	all->z = good_angles(all, all->z);
	all->hz = all->z + 45;
	all->lz = all->z - 45;
	all->hz = good_angles(all, all->hz);
	all->lz = good_angles(all, all->lz);
}

void	ray(t_all *all)
{
	sky_floor(all);
	every_ray(all, all->lz);
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
		camera_turn(all, 1);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		camera_turn(all, 2);
	else
		return (0);
	ray(all);
	return (1);
}

void	my_hook(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->g_img = mlx_texture_to_image(all->mlx, all->texture);
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		ft_exit("BYE <3", 1);
	press_keys(keydata, all);
	draw_minimap(all);
}

void	sky_floor(t_all *all)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (y ++ < HEIGHT / 2)
	{
		while (x ++ < WIDTH)
			mlx_put_pixel(all->background, x, y, 0x8989ff);
		x = -1;
	}
	y = HEIGHT / 2;
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
	all.z = 270;
	all.lz = 270 - 45;
	all.hz = 270 + 45;
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	if (all.mlx)
		mlx_set_window_title(all.mlx, "Cub3d");
	else
		ft_exit("error\n-MLX PROBLEM-", -1);
	all.background = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	//mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	all.texture = mlx_load_png("grass.png");
	all.g_img = mlx_texture_to_image(all.mlx, all.texture);
	ray(&all);
	draw_minimap(&all);
//	printf ("starting at (%f, %f)\n", all.x, all.y);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (0);
}
