/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:06:35 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:45:16 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_player_pos(t_all *all)
{
	if ((int)all->x != (int)all->oldx || (int)all->y != (int)all->oldy)
	{
		if (all->map[(int)all->oldy][(int)all->oldx] != 2)
			all->oldchar = all->map[(int)all->oldy][(int)all->oldx];
		all->map[(int)all->oldy][(int)all->oldx] = all->oldchar;
		all->map[(int)all->y][(int)all->x] = 2;
		all->oldx = all->x;
		all->oldy = all->y;
	}
}

int	get_sum(double x, double ray)
{
	if (x < ray)
		return (1);
	else
		return (-1);
}

void	draw_fov(t_all *all, int start_y, int start_x, int i)
{
	double	y;
	double	ray_y;
	double	ray_x;
	double	sum_y;

	y = (all->y * 8) - (start_y * 8);
	all->w = (all->x * 8) - (start_x * 8);
	ray_y = (all->ray_hits[i][0] * 8) - (start_y * 8);
	ray_x = (all->ray_hits[i][1] * 8) - (start_x * 8);
	all->m = ((ray_y) - y) / ((ray_x) - all->w);
	all->n = (((all->y * 8) - (start_y * 8)) - (all->m * all->w));
	sum_y = get_sum(y, ray_y);
	while ((int)y != (int)ray_y)
	{
		all->w = (y - all->n) / all->m;
		if (all->w < all->map_width * 8 && all->w >= 0 && y < all->map_height
			* 8 && y >= 0 && (int)all->w < 256 && (int)y < 256)
			mlx_put_pixel(all->background, (int)all->w, (int)y, 0x0000ffff);
		y += sum_y;
	}
}

void	draw_ray_minimap(t_all *all, int start_y, int start_x)
{
	double	x;
	double	ray_y;
	double	ray_x;
	double	sum_x;
	int		i;

	i = 0;
	while (i < WIDTH - 1)
	{
		x = (all->x * 8) - (start_x * 8);
		ray_y = all->ray_hits[i][0] * 8;
		ray_x = (all->ray_hits[i][1] * 8) - (start_x * 8);
		all->m = (ray_y - (all->y * 8)) / (ray_x - x);
		all->n = (((all->y * 8) - (start_y * 8)) - (all->m * x));
		sum_x = get_sum(x, ray_x);
		while ((int)x != (int)ray_x)
		{
			all->h = (all->m * x) + all->n;
			if (x < all->map_width * 8 && x >= 0 && all->h < all->map_height
				* 8 && all->h >= 0 && (int)x < 256 && (int)all->h < 256)
				mlx_put_pixel(all->background, (int)x, (int)all->h, 0x0000ffff);
			x += sum_x;
		}
		draw_fov(all, start_y, start_x, i++);
	}
}
