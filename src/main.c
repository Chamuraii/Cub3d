/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/05 17:52:39 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sky_floor(t_all *all);

void	ft_exit(char *reason, int status)
{
	ft_printf("%s\n", reason);
	exit(status);
}

void	texture_load(t_all *all, char *text)
{
	free(all->texture->pixels);
	free(all->texture);
	all->texture = mlx_load_png(text);
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
	int		pix;
	int		end;
	int		i;

	pix = HEIGHT / 10 - (dist - 2) * HEIGHT / 100;
	end = pix * 8;
	i = HEIGHT - end;
	rad += 45;
//	printf("------------------------- rad = %f\n", rad);
//	printf ("drawing a line from %d to %d, for %f m at %f degres (x = %f)\n", i, end, dist, rad, - rad / 45 * WIDTH + WIDTH);
	while (i < end && i >= 0)
	{
		if (rad == 0)
			mlx_put_pixel(all->background, WIDTH / 2, i, 0x0000ff);
		else /* if (rad >= 45) */
			mlx_put_pixel(all->background, -rad / 45
				* WIDTH + WIDTH, i, 0x0000ff);
/* 		else if (rad < 45)
			mlx_put_pixel(all->background, rad / 45
				* WIDTH + WIDTH, i, 0x00ff00); */
		i ++;
	}
}

double	cadran(t_all *all, double rad)
{
	double	a;

	a = 0;
	rad = good_angles(all, rad);
	if (rad > 0 && rad < 90)
	{
		a = cos(rad * PI / 180) / sin(rad * PI / 180);
	//	printf ("cad 1\n");
	}
	else if (rad > 90 && rad < 180)
	{
		a = -cos(rad * PI / 180) / sin(rad * PI / 180);
		//printf ("cad 2\n");
	}
	else if (rad > 180 && rad < 270)
	{
		a = cos(rad * PI / 180) / sin(rad * PI / 180);
		//printf ("cad 3\n");
	}
	else if (rad > 270 && rad < 360)
	{
		a = -cos(rad * PI / 180) / sin(rad * PI / 180);
		//printf ("cad 4\n");
	}
	else
		a = 1;
	//printf("a == %f\n", a);
	return (a);
}

double	change_x(t_all *all, double rad, double a, double x)
{
	if (rad + all->z < 90 && rad + all->z > 0)
	{
		x -= a;
		//printf ("x 1\n");
	}
	else if (rad + all->z < 180 && rad + all->z > 90)
	{
		x += a;
		//printf ("x 2\n");
	}
	else if (rad + all->z < 270 && rad + all->z > 180)
	{
		x += a;
		//printf ("x 3\n");
	}
	else
	{
		x -= a;
	//	printf ("x 4\n");
	}
	return (x);
}

double	change_y(t_all *all, double rad, double a, double y)
{
	if (rad + all->z < 90 && rad + all->z > 0)
		y += a;
	else if (rad + all->z < 180 && rad + all->z > 90)
		y += a;
	else if (rad + all->z < 270 && rad + all->z > 180)
		y -= a;
	else
		y -= a;
	return (y);
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
		if (rad == 0 || rad == 90 || rad == 180 || rad == 270)
			rad += 5;
		a = cadran (all, good_angles(all, rad + all->z));
		printf("a = %f\n", a);
		x = 0;
		y = 0;
		while (x + all->x < all->map_width && floor(y / a + all->y) < all->map_height - 1
			&& x + all->x >= 0 && y / a + all->y >= 0 && !(all->map[(int)floor(y / a + all->y)]
				[(int)floor(x + all->x)] == 1 || (x + a + all->x > ceil(x + all->x)
					&& all->map[(int)floor(y / a + all->y)][(int)ceil(x + all->x)] == 1)))
		{
			printf("checking (%f, %f) // (%f, %f)... %f\n", x , y / a, ceil(x), y / a, all->lz + rad);
			dist = sqrt(pow(x - all->x, 2) + pow((y / a) - all->y, 2));
			draw_pixel_line(all, dist, good_angles(all, rad + all->z));
			printf("cadraddd %f\n", good_angles(all, rad + all->z));
			a = cadran (all, good_angles(all, rad + all->z));
			all->ray_hits[i][0] = floor(y / a + all->y);
			if (x + a + all->x > ceil(x + all->x))
				all->ray_hits[i++][1] = ceil(x + all->x);
			else
				all->ray_hits[i++][1] = x + all->x;
			x = change_x(all, rad, a, x);
			y = change_y(all, rad, a, y);
			printf("rad == %f\n", rad + all->z);
		}
	//	printf ("du coup (%d,%d) %f\n", (int)floor(y / a), (int)floor(x), all->lz + rad);
		rad += 2;
		if (rad == 0 || rad == 90 || rad == 180 || rad == 270)
			rad += 2;
		all->ray_hits[i][0] = -1;
		all->ray_hits[i][1] = -1;
	}
}

void	camera_turn(t_all *all, int i)
{
	if (i == 1)
	{
		printf ("look right\n");
		all->z -= 5;
	}
	if (i == 2)
	{
		printf ("look left\n");
		all->z += 5;
	}
	while (all->z < 0)
		all->z += 360;
	while (all->z >= 360)
		all->z -= 360;
	all->hz = all->z + 45;
	all->lz = all->z - 45;
	while (all->hz < 0)
		all->hz += 360;
	while (all->hz >= 360)
		all->hz -= 360;
	while (all->lz < 0)
		all->lz += 360;
	while (all->lz >= 360)
		all->lz -= 360;
	printf ("(%f) -> %f to %f visible\n", all->z, all->hz, all->lz);
}

void	ray(t_all *all)
{
	sky_floor(all);
	every_ray(all, all->lz);
}

void	press_keys(mlx_key_data_t keydata, t_all *all)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		//printf ("%d\n",all->map[(int)floor(all->y - (sin((all->z + 90) * PI / 180)))]
		//	[(int)floor(all->x + (cos((all->z + 90) * PI / 180)))]);
	//	printf("(%d, %d)\n", (int)floor(all->y - (sin((all->z + 90) * PI / 180))), (int)floor(all->x + (cos((all->z + 90) * PI / 180))));
		if (all->map[(int)floor(all->y - (sin((all->z + 90) * PI / 180)))]
			[(int)floor(all->x + (cos((all->z + 90) * PI / 180)))] != 1)
		{
			all->x += cos((all->z + 90) * PI / 180);
			all->y -= sin((all->z + 90) * PI / 180);
			printf ("going right to (%f, %f)\n", all->y, all->x);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		//printf ("%d\n", all->map[(int)floor(all->y - (sin(all->z * PI / 180)))]
		//	[(int)floor(all->x - (cos(all->z * PI / 180)))]);
		//printf("(%d, %d)\n", (int)floor(all->y - (sin(all->z * PI / 180))), (int)floor(all->x - (cos(all->z * PI / 180))));
		if (all->map[(int)floor(all->y - (sin(all->z * PI / 180)))]
			[(int)floor(all->x - (cos(all->z * PI / 180)))] != 1)
		{
			all->x -= cos(all->z * PI / 180);
			all->y -= sin(all->z * PI / 180);
			printf ("going down to (%f, %f)\n", all->y, all->x);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
	//	printf ("%d\n",all->map[(int)floor(all->y + (sin(all->z * PI / 180)))]
		//	[(int)floor(all->x - (cos(all->z * PI / 180)))]);
		//printf("(%d, %d)\n", (int)floor(all->y + (sin(all->z * PI / 180))), (int)floor(all->x + (cos(all->z * PI / 180))));
		if (all->map[(int)floor(all->y + (sin(all->z * PI / 180)))]
			[(int)floor(all->x - (cos(all->z * PI / 180)))] != 1)
		{
			all->x -= cos(all->z * PI / 180);
			all->y += sin(all->z * PI / 180);
			printf ("going up to (%f, %f)\n", all->y, all->x);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
	//	printf ("%d\n", all->map[(int)floor(all->y + (sin((all->z - 90) * PI / 180)))]
		//	[(int)floor(all->x + (cos((all->z - 90) * PI / 180)))]);
		//printf("(%d, %d)\n", (int)floor(all->y + (sin((all->z - 90) * PI / 180))), (int)floor(all->x + (cos((all->z - 90) * PI / 180))));
		if (all->map[(int)floor(all->y + (sin((all->z - 90) * PI / 180)))]
			[(int)floor(all->x + (cos((all->z - 90) * PI / 180)))] != 1)
		{
			all->x += cos((all->z - 90) * PI / 180);
			all->y += sin((all->z - 90) * PI / 180);
			printf ("going left to (%f, %f)\n", all->y, all->x);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
	{
		camera_turn(all, 1);
		ray(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
	{
		camera_turn(all, 2);
		ray(all);
	}
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

void	window(t_all *all)
{
	all->texture = mlx_load_png("grass.png");
	if (!all->texture)
		ft_exit("error\n-GRASS TEXTURE NOT LOADED-", -1);
	all->g_img = mlx_texture_to_image(all->mlx, all->texture);
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
	if (!main_validator(&all, argv))
		return (ft_printf ("Error\n"), -1);
	else
		ft_printf ("Map validation successful!\n");
	ft_printf ("hello\n");
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
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	window(&all);
	ray(&all);
	draw_minimap(&all);
	printf ("starting at (%f, %f)\n", all.x, all.y);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	//ft_free(&all);
	return (0);
}
