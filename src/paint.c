/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:37:11 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/13 20:38:22 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* BACKGROUND : paints the sky and the floor with the colors given by the map */

void	background(t_all *all)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (y ++ < HEIGHT / 2 - 1)
	{
		while (x ++ < WIDTH)
			mlx_put_pixel(all->background, x, y, all->ceiling_color);
		x = -1;
	}
	y = HEIGHT / 2 - 1;
	while (y ++ < HEIGHT - 1)
	{
		while (x ++ < WIDTH)
			mlx_put_pixel(all->background, x, y, all->floor_color);
		x = -1;
	}
}

/* DRAW_PIXEL_LINE : draws the walls by calculating their size (depending on the
distance), and their position (depending on the relative angle)*/

void	draw_pixel_line(t_all *all, double dist, double rad)
{
	double		i;
	int			start;
	int			end;
	int			wide;

	i = 1;
	if (dist > 1)
		i = 1 / dist;
	start = (HEIGHT * (1 - i)) / 2;
	wide = -rad * WIDTH / FOV - 1;
	if (rad == 0)
		wide = WIDTH - 2;
	end = HEIGHT - start;
	start ++;
	while (start < end && start > 0)
	{
		if (dist >= 1)
			mlx_put_pixel(all->background, wide, start, get_pixel_color(
					all, (double)(end - (HEIGHT * (1 - 1 / dist) / 2))));
		else
			mlx_put_pixel(all->background, wide, start, get_pixel_color(
					all, (double)(end - (HEIGHT * (1 - 1 / dist)))));
		++start;
	}
}

/* WHAT_SIDE : depending on the side the player is looking at and the shortest
distance, picks the right texture to draw */

void	what_side(t_all *all, double rad)
{
	if (rad < 180 && all->dir == 0)
		all->side = all->south;
	else if (rad < 90 && all->dir == 1)
		all->side = all->west;
	else if (rad < 270 && all->dir == 1)
		all->side = all->east;
	else if (all->dir == 0)
		all->side = all->north;
	else
		all->side = all->west;
}
