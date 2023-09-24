/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/09/22 17:41:09 by jchamak          ###   ########.fr       */
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

	if (dist >= 2)
	{
		i = - log(dist / 30) * 140;
		end = HEIGHT / 2 + i / 2;
		i = HEIGHT - end;
		//printf ("drawing a line from %d to %d, for %f m\n", i, end, dist);
	}
	else
	{
		i = (-1.15 * dist + 5) * 140;
		end = HEIGHT / 2 + i / 2;
		i = HEIGHT - end;
		//printf ("drawing a line from %d to %d, for %f m\n", i, end, dist);
	}
	rad = good_angles(all, rad);
	wide = rad * WIDTH / FOV;
	if (rad == 0)
		wide = WIDTH + 1;
	i += 2;
	//printf ("drawing a line from %d to %d, for %f m at %f degres (x = %d)\n", i, end, dist, rad, wide);
	while (i <= end && i > 0)
		mlx_put_pixel(all->background, -wide, i ++, 0xff0000);
}

double	distance(t_all *all, double rad, int i)
{
	double	n;

	//printf("-- %f -> %f\n", all->z - rad, cos(rad * PI / 180));
	if (rad == 0 | rad == 90 || rad == 180 || rad == 270)
		return (100);
	n = sqrt(pow(all->ray_hits[i][1] - all->x, 2) + pow(all->ray_hits[i][0] - all->y, 2));
	n *= (cos((all->z - rad) * PI / 180));
	return (n);
}

void	good_rays(t_all *all, int i)
{
	if (all->ray_hits[i][0] < 0)
		all->ray_hits[i][0] = 0;
	if (all->ray_hits[i][0] >= all->map_height)
		all->ray_hits[i][0] = all->map_height - 0.1;
	if (all->ray_hits[i][1] < 0)
		all->ray_hits[i][1] = 0;
	if (all->ray_hits[i][1] >= all->map_width)
		all->ray_hits[i][1] = all->map_width - 0.1;
}

double	testxx(t_all *all, double rad, double x)
{
	if (rad < 270 && rad > 90)
		return (ceil(all->x + x));
	else
		return (floor(all->x + x));
}


double	testyy(t_all *all, double rad, double y)
{
	if (rad < 180)
		return (ceil(all->y + y));
	else
		return (floor(all->y + y));
}

int	is_wall_h(t_all *all, int i, int rad)
{
	//printf("%d, %d ===\n", (int)all->ray_hits[i][0], (int)all->ray_hits[i][1]);
	//printf("%d :: \n", all->map[(int)all->ray_hits[i][0]][(int)all->ray_hits[i][1]]);
	if (all->map[(int)all->ray_hits[i][0]][(int)all->ray_hits[i][1]] == 1) // segfault
	{
		if (rad < 180)
			all->ray_hits[i][0] = (int)all->ray_hits[i][0];
		else
			all->ray_hits[i][0] /* = (int)all->ray_hits[i][0]  */++;
		all->finaly = all->ray_hits[i][1];
		all->finalx = all->ray_hits[i][0];
		all->finald = 0;
		return (1);
	}
	if (all->ray_hits[i][0] <= 0 || all->ray_hits[i][0] >= all->map_height
		|| all->ray_hits[i][1] <= 0 || all->ray_hits[i][1] >= all->map_width)
		return (1);
	return (0);
}


int	is_wall_v(t_all *all, int i, int rad)
{
	//printf("%d, %d ===\n", (int)all->ray_hits[i][0], (int)all->ray_hits[i][1]);
	//printf("%d :: \n", all->map[(int)all->ray_hits[i][0]][(int)all->ray_hits[i][1]]);
	if (all->map[(int)all->ray_hits[i][0]][(int)all->ray_hits[i][1]] == 1)
	{
		if (all->distv < all->disth)
		{
			all->dist = all->distv;
			if (rad < 270 && rad > 90)
				all->ray_hits[i][1] = (int)all->ray_hits[i][1];
			else
				all->ray_hits[i][1] ++;
			all->finaly = all->ray_hits[i][1];
			all->finalx = all->ray_hits[i][0];
			all->finald = 1;
		}
		return (1);
	}
	if (all->ray_hits[i][0] <= 0 || all->ray_hits[i][0] >= all->map_height
		|| all->ray_hits[i][1] <= 0 || all->ray_hits[i][1] >= all->map_width)
		return (1);
	return (0);
}

void	ver(t_all *all, int i, double rad)
{
	double	testxv;
	double	testyv;
	int		plusxv;

	plusxv = 0;
	while (1)
	{
		if (rad == 0 || rad == 90 || rad == 180 || rad == 270)
			rad ++;
		testxv = testxx(all, good_angles(all, rad + all->lz), plusxv);
		testyv = all->y - (tan(good_angles(all, rad + all->lz - 180) * PI / 180) * (testxv - all->x));
		all->ray_hits[i][0] = testyv;
		all->ray_hits[i][1] = testxv;
		good_rays(all, i);
	//	printf("trying %f %f.. %f\n", all->ray_hits[i][1], all->ray_hits[i][0], good_angles(all, rad + all->lz));
		if (is_wall_v(all, i, good_angles(all, rad + all->lz)))
		{
			all->distv = distance(all, good_angles(all, rad + all->lz), i);
			printf("distv = %f\n", all->distv);
			break;
		}
		if (good_angles(all, rad + all->lz) < 270 && good_angles(all, rad + all->lz) > 90)
			plusxv ++;
		else
			plusxv --;
	}
}

void	hor(t_all *all, int i, double rad)
{
	double	testxh;
	double	testyh;
	int		plusyh;

	plusyh = 0;
	while (1)
	{
		if ( good_angles(all, rad + all->lz) == 0 ||  good_angles(all, rad + all->lz) == 90 
			||  good_angles(all, rad + all->lz) == 180 ||  good_angles(all, rad + all->lz) == 270)
			rad ++;
		testyh = testyy(all, good_angles(all, rad + all->lz), plusyh);
		testxh = all->x + (tan(good_angles(all, rad + all->lz - 90) * PI / 180) * (testyh - all->y));
		if (testxh > all->map_width) //
		{
			testxh = all->x + 10 * (testyh - all->y); //
			break;
		}
		//printf("testx %f %f\n", testxh, (good_angles(all, rad + all->lz - 90)));
		all->ray_hits[i][0] = testyh;
		all->ray_hits[i][1] = testxh;
		good_rays(all, i);
		//printf("trying %f %f\n", all->ray_hits[i][1], all->ray_hits[i][0]);
		if (is_wall_h(all, i, good_angles(all, rad + all->lz)))
		{
			all->disth = distance(all, good_angles(all, rad + all->lz), i);
			all->dist = all->disth;
			printf("disth = %f\n", all->disth);
			break;
		}
		if (good_angles(all, rad + all->lz) < 180)
			plusyh ++;
		else
			plusyh --;
	}
}

void	rays(t_all *all)
{
	double	rad;
	int		i;

	rad = 0;
	i = 0;
	while (rad <= FOV)
	{
		hor(all, i, rad);
		ver(all, i, rad);
		i ++;
		//rad += 5;
		rad += 0.03;
		printf("final %f,%f = %d\n", all->finalx, all->finaly, all->finald);
		printf("FINAL dist = %f\n", all->dist);
		draw_pixel_line(all, all->dist, good_angles(all, rad));
		all->ray_hits[i][1] = all->finaly;
		all->ray_hits[i][0] = all->finalx;
	}
	all->ray_hits[i][0] = -1;
	all->ray_hits[i][1] = -1;
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
	rays(all);
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
	ray(&all);
//	printf ("starting at (%f, %f)\n", all.x, all.y);
	mlx_key_hook(all.mlx, &my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (0);
}
