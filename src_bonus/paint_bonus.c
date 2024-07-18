/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:37:11 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/15 18:13:14 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_texture_orientation(t_all *all, double range)
{
	all->range = range;
	if (all->ray_num >= WIDTH)
		all->ray_num = 0;
	if (!all->dir)
	{
		all->texture_x = all->ray_hits[all->ray_num][1];
		if (all->ray_hits[all->ray_num][0] < all->y)
			all->texture_x = all->texture_x - (int)all->texture_x;
		else
			all->texture_x = 1 - (all->texture_x - (int)all->texture_x);
	}
	else
	{
		all->texture_x = all->ray_hits[all->ray_num][0];
		if (all->ray_hits[all->ray_num][1] > all->x)
			all->texture_x = all->texture_x - (int)all->texture_x;
		else
			all->texture_x = 1 - (all->texture_x - (int)all->texture_x);
	}
	all->texture_x = (all->side->width - 1) * all->texture_x;
}

void	draw_pixel_line(t_all *all, double dist)
{
	double		i;
	int			start;
	int			end;

	i = 1 / dist;
	start = (HEIGHT * (1 - i)) / 2;
	end = (HEIGHT * (1 + i)) / 2;
	ft_texture_orientation(all, end - start);
	all->texture_counter = start;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	i = 0;
	while (i < start)
			mlx_put_pixel(all->background, all->ray_num, i++, all->ceiling_color);
	while (start < end)
	{
		mlx_put_pixel(all->background, all->ray_num, start, get_pixel_color(
				all, all->side->height / all->range, start - all->texture_counter));
		++start;
	}
	while (end < HEIGHT)
			mlx_put_pixel(all->background, all->ray_num, end++, all->floor_color);
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
