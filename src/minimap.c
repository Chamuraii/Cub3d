/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:21:03 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/02 20:21:03 by jorgfern         ###   ########.fr       */
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



void	draw_ray_minimap(t_all *all)
{
	double	m;
	double n;
	double y;
	double x = all->x * 16;
	double ray_y;
	double	ray_x;
	double sum_x;

	for (int i = 0; all->ray_hits[i][0] != -1; i++)
	{
		ray_y = all->ray_hits[0][0] * 16;
		ray_x = all->ray_hits[0][1] * 16;
		m = ((ray_y) - all->y * 16) / ((ray_x) - x);
		n = (((all->y * 16) - (m * x)));
		if (x < ray_x)
			sum_x = 1;
		else
			sum_x = -1;
		while ((int)x * 16 != (int)ray_x * 16)
		{
			y = (m * x) + n;
			mlx_put_pixel(all->background, (int)x, (int)y, 0x0000ffff);
			x += sum_x;
		}
	}

}

void	draw_minimap(t_all *all)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	i;
	uint32_t	j;

	update_player_pos(all);
	y = 0;
	while (y < all->map_height)
	{
		x = 0;
		while (x < all->map_width)
		{
			if (all->map[y][x] == 0)
			{
				for (i = y * 16; i < (y * 16) + 16; ++i)
				{
					for (j = x * 16; j < (x * 16) + 16; ++j)
						mlx_put_pixel(all->background, j, i, 0xffffffff);
				}
			}
			else if (all->map[y][x] == 1)
			{
				for (i = y * 16; i < (y * 16) + 16; ++i)
				{
					for (j = x * 16; j < (x * 16) + 16; ++j)
						mlx_put_pixel(all->background, j, i, 0x000000ff);
				}
			}
			else if (all->map[y][x] == 2)
			{
				for (i = y * 16; i < (y * 16) + 16; ++i)
				{
					for (j = x * 16; j < (x * 16) + 16; ++j)
						mlx_put_pixel(all->background, j, i, 0xff0000ff);
				}
			}
			x++;
		}
		y++;
	}
	draw_ray_minimap(all);
}