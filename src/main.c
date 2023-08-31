/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/31 16:53:03 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sky_floor(t_all *all);
void	center_ray(t_all *all);

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

void	draw_pixel_line(t_all *all, double dist, double rad)
{
	int		pix;
	int		end;
	int		i;
	double	pos;

	pix = 100 - (dist - 2) * 10;
	end = pix * 8;
	i = 1000 - end;
	pos = ((135 + rad) / 90) * 800;
	rad += 45;
	printf("rad = %f, pos = %f\n", rad, pos);
	printf ("drawing a line from %d to %d, for %f m at %f degres (x = %f)\n", i, end, dist, rad, - rad / 45 * 1600 + 1600);
	while (i < end && i >= 0 && rad >= 0 && rad <= 90)
	{
		if (rad == 0)
			mlx_put_pixel(all->background, 800, i, 0x0000ff);
		else if (rad >= 45)
			mlx_put_pixel(all->background, rad / 45 * 1600 + 1600, i, 0x0000ff);
		else if (rad < 45)
			mlx_put_pixel(all->background, -rad / 45 * 1600 + 1600, i, 0x0000ff);
		i ++;
	}
}

void	every_ray(t_all *all)
{
	double	x;
	double	a;
	double	dist;
	double	rad;
	double	mrad;

	rad = all->lz;
	mrad = all->hz;
	printf("an (%f, %f)\n", rad, mrad);
	a = fabs(cos(rad * PI / 180)) / fabs(sin(rad * PI / 180));
	x = all->x;
	printf("----x = %f, a = %f\n", x, a);
	//printf("checking (%f , %f)\n", floor(x), floor(y));
	center_ray(all);
	x += a;
	while (x < 10 && floor(x / a) < 10 && x > 0 && x / a > 0)
	{
		a = fabs(cos(rad * PI / 180)) / fabs(sin(rad * PI / 180));
		//x += a;
		printf("checkingg (%f, %f)\n", floor(x), floor(x / a));
		if (all->map[(int)floor(x / a)][(int)floor(x)] == 1 && x + a < 10 && x / a < 10 && x > 0 && x / a > 0)
		{
			dist = sqrt(pow(/* floor(x) */x - all->x, 2) + pow((x / a) - all->y, 2));
			printf("knocked x in %d %d at %f m (%f deg)\n",
				(int)floor(x / a), (int)floor(x), dist, rad);
			draw_pixel_line(all, dist, rad - all->z);
		}
		else if (x + a > ceil(x) && x + a < 10 && x / a < 10 && x > 0 && x / a > 0)
		{
			printf("checkingg (%f, %f)\n", ceil(x), floor(x / a));
			if (all->map[(int)floor(x / a)][(int)ceil(x)] == 1) //ceil or floor or nothing (x / a)
			{
				dist = sqrt(pow(/* ceil(x) */x - all->x, 2)
						+ pow(/* floor(x / a) */x / a - all->y, 2));
				printf("knocked y in %d %d at %f m (%f deg)\n",
					(int)floor(x / a), (int)ceil(x), dist, rad);
				draw_pixel_line(all, dist, rad - all->z);
			}
		}
		rad += 0.05;
		x = all->x;
	}
}

void	center_ray(t_all *all)
{
	int		i;
	int		y;
	double	dist;
	int		pix;
	int		end;

	y = fabs(all->y);
	dist = 0;
	y = floor(y);
	while (all->map[(int)ceil(y)][(int)floor(all->x)] != 1)
	{
		y ++;
		dist ++;
	}
	//draw_pixel_line(all, dist, 0);
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
	every_ray(all);
}

void	press_keys(mlx_key_data_t keydata, t_all *all)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		if (all->map[(int)floor(all->y + sin((all->z - 90) * PI / 180))]
			[(int)floor(all->x + cos((all->z - 90) * PI / 180))] != 1)
		{
			all->x += cos((all->z + 90) * PI / 180);
			all->y += sin((all->z + 90) * PI / 180);
			printf ("going right to (%f, %f)\n", all->x, all->y);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		if (all->map[(int)floor(all->y - sin(all->z * PI / 180))]
			[(int)floor(all->x - cos(all->z * PI / 180))] != 1)
		{
			all->x -= cos(all->z * PI / 180);
			all->y -= sin(all->z * PI / 180);
			printf ("going down to (%f, %f)\n", all->x, all->y);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		if (all->map[(int)floor(all->y + sin(all->z * PI / 180))]
			[(int)floor(all->x + cos(all->z * PI / 180))] != 1)
		{
			all->x += cos(all->z * PI / 180);
			all->y += sin(all->z * PI / 180);
			printf ("going up to (%f, %f)\n", all->x, all->y);
			ray(all);
		}
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		if (all->map[(int)floor(all->y + sin((all->z + 90) * PI / 180))]
			[(int)floor(all->x + cos((all->z + 90) * PI / 180))] != 1)
		{
			all->x += cos((all->z - 90) * PI / 180);
			all->y += sin((all->z - 90) * PI / 180);
			printf ("going left to (%f, %f)\n", all->x, all->y);
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
}

void	window(t_all *all)
{
	all->texture = mlx_load_png("grass.png");
	if (!all->texture)
		ft_exit("error\n-GRASS TEXTURE NOT LOADED-", -1);
	all->g_img = mlx_texture_to_image(all->mlx, all->texture);
	//mlx_image_to_window(all->mlx, all->g_img, 780, 700);
}

void	sky_floor(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y ++ < 500)
	{
		while (x ++ < 1599)
			mlx_put_pixel(all->background, x, y, 0x8989ff);
		x = 0;
	}
	y = 500;
	while (y ++ < 999)
	{
		while (x ++ < 1599)
			mlx_put_pixel(all->background, x, y, 0xff9e3d);
		x = 0;
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
	all.z = 90;
	all.lz = 45;
	all.hz = 135;
	all.mlx = mlx_init(1600, 1000, "MLX42", 0);
	if (all.mlx)
		mlx_set_window_title(all.mlx, "Cub3d");
	else
		ft_exit("error\n-MLX PROBLEM-", -1);
	all.background = mlx_new_image(all.mlx, 1600, 1000);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
//	window(&all);
	sky_floor(&all);
	center_ray(&all);
	every_ray(&all);
	printf ("starting at (%f, %f)\n", all.x, all.y);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	//ft_free(&all);
	return (0);
}
