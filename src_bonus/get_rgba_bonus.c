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

unsigned int	get_rgb(mlx_texture_t *side, uint32_t y, double x)
{
	uint32_t xy;

	xy = (int)(y + round(x)) * 4;
	if ((y + round(x)) >= (side->height * side->width))
		return 0;
	return ((side->pixels[(int)xy] << 24)
			| (side->pixels[(int)xy + 1] << 16)
			| (side->pixels[(int)xy + 2] << 8)
			| (side->pixels[(int)xy + 3]));
}



unsigned int	get_pixel_color(t_all *all, double scale_y, double y)
{
	y = (int)(y * scale_y);
	return (get_rgb(all->side, y * all->side->width, all->texture_x));
}
