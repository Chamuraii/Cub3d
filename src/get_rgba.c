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



unsigned int	get_pixel_color(t_all *all, double scale_y, double y)
{
	y = (int)(y * scale_y);
	return (get_rgb(all->side->pixels, all->side->width, y, all->texture_x));
}
