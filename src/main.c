/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/29 19:00:43 by jchamak          ###   ########.fr       */
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

void	every_ray(t_all *all)
{
	double	x;
	double	y;
	double	rad;
	double	mrad;

	rad = all->lz;
	mrad = all->hz - 1;
	printf("an (%f, %f)\n", rad, mrad);
	x = all->x;
	y = all->y + 1;
	while (rad < mrad)
	{
		if (cos(rad * PI / 180) == 0)
			rad ++;
		y = ceil(y);
		x += cos(rad * PI / 180) / sin(rad * PI / 180);
		//printf("checking (%f , %f)\n", floor(x), y);
		//if (all->map[floor(x)][y] == 1)
		//	break ;
		x = ceil(x);
		y += sin(rad * PI / 180) / cos(rad * PI / 180);
		//printf("checkingg (%f, %f)\n", x, floor(y));
		//if (all->map[x][floor(y)] == 1)
		//	break ;
		rad ++;
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
	dist = ceil(y) - y;
	y = ceil(y);
	//while (all->map[floor(x)][ceil(y)] != 1)
	while (y < 4)
		y ++;
	dist += y;
	pix = 100 - (dist - 1) * 10;
	printf ("pix = %d\n", pix);
	i = pix * 14;
	end = (100 - pix) * 14;
	printf ("i = %d\n", i);
	printf ("end = %d\n", end);
	while (i < end && i >= 0)
	{
		mlx_put_pixel(all->background, 1300, i, 0x0000ff);
		i ++;
	}
}

void	camera_turn(t_all *all, int i)
{
	if (i == 1)
	{
		printf ("look right\n");
		all->z -= 15;
	}
	if (i == 2)
	{
		printf ("look left\n");
		all->z += 15;
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
	printf ("(%d) -> %d to %d visible\n", all->z, all->hz, all->lz);
}

void	ray(t_all *all)
{
	sky_floor(all);
	printf ("calling center\n");
	center_ray(all);
	//every_ray(all);
}

void	press_keys(mlx_key_data_t keydata, t_all *all)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		printf ("going right\n");
		all->x += cos((all->z - 90) * PI / 180);
		all->y += sin((all->z - 90) * PI / 180);
		printf ("(%f, %f)\n", all->x, all->y);
		ray(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		printf ("going down\n");
		all->x -= cos(all->z * PI / 180);
		all->y -= sin(all->z * PI / 180);
		printf ("(%f, %f)\n", all->x, all->y);
		ray(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		printf ("going up\n");
		all->x += cos(all->z * PI / 180);
		all->y += sin(all->z * PI / 180);
		printf ("(%f, %f)\n", all->x, all->y);
		ray(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		printf ("going left\n");
		all->x += cos((all->z + 90) * PI / 180);
		all->y += sin((all->z + 90) * PI / 180);
		printf ("(%f, %f)\n", all->x, all->y);
		ray(all);
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
	while (y ++ < 700)
	{
		while (x ++ < 2559)
			mlx_put_pixel(all->background, x, y, 0x8989ff);
		x = 0;
	}
	y = 700;
	while (y ++ < 1399)
	{
		while (x ++ < 2559)
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
	all.x = 0;
	all.y = 0;
	all.z = 90;
	all.mlx = mlx_init(2560, 1400, "MLX42", 0);
	if (all.mlx)
		mlx_set_window_title(all.mlx, "Cub3d");
	else
		ft_exit("error\n-MLX PROBLEM-", -1);
	all.background = mlx_new_image(all.mlx, 2560, 1400);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	window(&all);
	sky_floor(&all);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	ft_free(&all);
	return (0);
}
