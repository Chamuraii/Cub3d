/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:21:49 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:24:43 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	get_rgb(uint8_t *pixels, uint32_t width, uint32_t y, double x)
{
	return ((pixels[(int)((y * width) + round(x)) *4] << 24)
			| (pixels[(int)((y * width) + round(x)) *4 + 1] << 16)
			| (pixels[(int)((y * width) + round(x)) *4 + 2] << 8)
			| (pixels[(int)((y * width) + round(x)) *4 + 3]));
}

unsigned int	get_pixel_color(t_all *all, double range)
{
	mlx_texture_t	*texture;
	double			x;
	double			scale_y;
	int				y;

	texture = all->side;
	scale_y = (double)texture->height / range;
	if (range > HEIGHT && !all->texture_counter)
		all->texture_counter = (unsigned int)((round(range) - HEIGHT) / 2);
	y = (int)(all->texture_counter++ *scale_y);
	if (all->ray_hits[all->ray_num][1] == -1)
		all->ray_num = 0;
	if (!all->dir)
		x = all->ray_hits[all->ray_num][1];
	else
		x = all->ray_hits[all->ray_num][0];
	if (!all->dir && all->ray_hits[all->ray_num][0] < all->y)
		x = (x - (int) x);
	else if (all->dir && all->ray_hits[all->ray_num][1] > all->x)
		x = (x - (int) x);
	else
		x = 1 - (x - (int) x);
	x = (texture->width - 1) * x;
	return (get_rgb(texture->pixels, texture->width, y, x));
}
