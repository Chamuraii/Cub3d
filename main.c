/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/28 16:21:37 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ray_cast(t_all *all)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
/* 	printf ("x = %d\n", all->x);
	while ((all->x + dx) % 10 != 0)
	{
		printf ("dx = %d\n", dx);
		dx ++;
	}
	while ((all->y + dy) % 10 != 0)
	{
		printf ("dy = %d\n", dy);
		dy ++;
	}
	printf ("il manque %d, %d\n", dx, dy); */

	//while tab[x ++][y ++] != 1 && < map limits
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
	//ray_cast(all);
}

void	press_keys(mlx_key_data_t keydata, t_all *all)
{
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		printf ("going right\n");
		all->x ++;
		printf ("(%d, %d)\n", all->x, all->y);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		printf ("going down\n");
		all->y --;
		printf ("(%d, %d)\n", all->x, all->y);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		printf ("going up\n");
		all->y ++;
		printf ("(%d, %d)\n", all->x, all->y);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		printf ("going left\n");
		all->x --;
		printf ("(%d, %d)\n", all->x, all->y);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		camera_turn(all, 1);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		camera_turn(all, 2);
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
	return (0);
}
