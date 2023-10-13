/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:34:11 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/13 20:36:26 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* IS_WALL_* : if the tested position happens to be a wall, calculates its
distance from the player, we then have two distances, one representing the
closest horizontal wall and the other, the vertical */

int	is_wall_h(t_all *all, int rad, double x, double y)
{
	if (rad >= 180)
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
	if (rad >= 270 || rad < 90)
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

/* CAST : casts a ray, increasing until hitting a wall, first horizontally, then
vertically */

void	cast(t_all *all, double rad, int o)
{
	double	x;
	double	y;

	while (1)
	{
		y = floor(all->y - o);
		if (rad < 180)
			y = ceil(all->y + o);
		x = all->x + tan(good_angles(all, rad - 90) * PI / 180) * (y - all->y);
		o ++;
		if (is_wall_h(all, rad, x, y) || x > all->map_width)
			break ;
	}
	o = 0;
	while (1)
	{
		x = floor(all->x - o);
		if (rad < 270 && rad > 90)
			x = ceil(all->x + o);
		y = all->y - tan(good_angles(all, rad - 180) * PI / 180) * (x - all->x);
		o ++;
		if (is_wall_v(all, rad, x, y) || y > all->map_height)
			break ;
	}
}

/* RAYS : calls every raycasting function for each ray of the FOV */

void	rays(t_all *all)
{
	double	rad;
	int		i;

	rad = 0;
	i = 0;
	background(all);
	while (rad <= FOV)
	{
		cast(all, good_angles(all, rad + all->z - FOV / 2), 0);
		final(all, i);
		i++;
		all->ray_hits[i][0] = -1;
		all->ray_hits[i][1] = -1;
		what_side(all, good_angles(all, rad + all->z - FOV / 2));
		draw_pixel_line(all, all->dist[0], good_angles(all, rad));
		all->ray_num++;
		all->texture_counter = 0;
		rad += 0.042;
	}
	all->ray_hits[i][0] = -1;
	all->ray_hits[i][1] = -1;
	draw_minimap(all);
}

/* FINAL : after getting two distances from the player's position to the closest
wall, keeps the data of the closest one (H or V) */

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
