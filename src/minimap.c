/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:21:03 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/14 16:30:57 by jchamak          ###   ########.fr       */
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



void	draw_ray_minimap(t_all *all, int start_y, int start_x)
{
	double	m;
	double n;
	double y = (all->y * 8) - (start_y * 8);
	double x = all->x * 8;
	double ray_y;
	double	ray_x;
	double sum_x;
	double sum_y;

	for (int i = 0; all->ray_hits[i][0] != -1; i++)
	{
		x = (all->x * 8) - (start_x * 8);
		ray_y = (all->ray_hits[i][0] * 8) - (start_y * 8);
		ray_x = (all->ray_hits[i][1] * 8) - (start_x * 8);
		m = ((ray_y) - (all->y * 8) - (start_y * 8)) / ((ray_x) - x);
		n = ((((all->y * 8) - (start_y * 8)) - (m * x)));

		if (x < ray_x)
			sum_x = 1;
		else
			sum_x = -1;
		while ((int)x != (int)ray_x) // segfault here ??
		{
			y = (m * x) + n;
			if (x < (all->map_width * 8) && x >= 0 && y < (all->map_height * 8) && y >= 0 && (int)x < (16 * 16) && (int)y < (16 * 16))
				mlx_put_pixel(all->background, (int)x, (int)y, 0x0000ffff);
			x += sum_x;
		}
		y = (all->y * 8) - (start_y * 8);
		x = (all->x * 8) - (start_x * 8);
		ray_y = (all->ray_hits[i][0] * 8) - (start_y * 8);
		ray_x = (all->ray_hits[i][1] * 8) - (start_x * 8);
		m = ((ray_y) - (all->y * 8) - (start_y * 8)) / ((ray_x) - x);
		n = ((((all->y * 8) - (start_y * 8)) - (m * x)));
		if (y < ray_y)
			sum_y = 1;
		else
			sum_y = -1;
		while ((int)y != (int)ray_y)
		{
			x = (y - n) / m;
			if (x < (all->map_width * 8) && x >= 0 && y < (all->map_height * 8) && y >= 0 && (int)x < (16 * 16) && (int)y < (16 * 16))
				mlx_put_pixel(all->background, (int)x, (int)y, 0x0000ffff);
			y += sum_y;
		}

	}

}

void	draw_minimap(t_all *all)
{
	int	y = 0;
	int	x = 0;
	int	i;
	int	j;
	int y_offset_u = 0;
	int x_offset_l = 0;
	int y_offset_d = 0;
	int x_offset_r = 0;
	int start_offset_y;
	int start_offset_x;
	int player_dist = 16;

	update_player_pos(all);
	y = (int)round(all->y) - 16;
	if (y < 0)
	{
		y_offset_u = -y;
		y = 0;
	}
	start_offset_y = y;
	if (y >= all->map_height - 32  && all->map_height > 32)
		y = all->map_height - 32;
	if (start_offset_y > all->map_height - 32  && all->map_height > 32)
		start_offset_y = (int)all->map_height - 32;
	while (y < (int)round(all->y) + 16 + y_offset_u && y < all->map_height)
	{
		x = (int)round(all->x) - 16;
		if (x < 0)
		{
			x_offset_l = -x;
			x = 0;
		}
		if (x + 16 > all->map_width - 16 && all->map_width > 32)
			x = (int)all->map_width - 32;
		start_offset_x = x;
		if (start_offset_x >= all->map_width - 32 && all->map_width > 32)
			start_offset_x = (int)all->map_width - 32;
		if (((int)round(all->x) + player_dist) > all->map_width)
			player_dist = -((int)round(all->x) - (int)all->map_width);
		while (x < (int)round(all->x) + player_dist + x_offset_l && x < all->map_width)
		{
			if (all->map[y][x] == 0)
			{
				for (i = y * 8; i < (y * 8) + 8; ++i)
				{
					for (j = x * 8; j < (x * 8) + 8; ++j)
						mlx_put_pixel(all->background, j - (start_offset_x * 8), i - (start_offset_y * 8), 0xffffffff);
				}
			}
			else if (all->map[y][x] == 1)
			{
				for (i = y * 8; i < (y * 8) + 8; ++i)
				{
					for (j = x * 8; j < (x * 8) + 8; ++j)
						mlx_put_pixel(all->background, j - (start_offset_x * 8), i - (start_offset_y * 8), 0x000000ff);
				}
			}
			else if (all->map[y][x] == 2)
			{
				for (i = y * 8; i < (y * 8) + 8; ++i)
				{
					for (j = x * 8; j < (x * 8) + 8; ++j)
						mlx_put_pixel(all->background, j - (start_offset_x * 8), i - (start_offset_y * 8), 0xff0000ff);
				}
			}
			x++;
		}
		y++;
	}
	draw_ray_minimap(all, start_offset_y, start_offset_x);
}