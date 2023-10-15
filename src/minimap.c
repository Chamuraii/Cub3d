/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:21:03 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/28 15:07:32 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	paint_map(t_all *all, int offset_x, int offset_y, unsigned int color)
{
	int	i;
	int	j;

	i = all->a * 8;
	while (i < (all->a * 8) + 8)
	{
		j = all->b * 8;
		while (j < (all->b * 8) + 8)
			mlx_put_pixel(all->background, j++
				- (offset_x * 8), i - (offset_y * 8), color);
		++i;
	}
}

void	paint_map_player(t_all *all, int offset_x, int offset_y)
{
	int	i;
	int	j;

	i = all->a * 8;
	while (i < (all->a * 8) + 4)
	{
		j = all->b * 8;
		while (j < (all->b * 8) + 4)
			mlx_put_pixel(all->background, j++ + (int)((all->x * 8)
					- ((int)all->x * 8) - 2) -(offset_x * 8),
				i + (int)((all->y * 8) - ((int)all->y * 8)
					- 2) - (offset_y * 8), 0xff0000ff);
		++i;
	}
}

void	minimap_init_y(t_all *all, int *offset_y, int *y_off_u)
{
	all->a = (int)round(all->y) - 16;
	if (all->a < 0)
	{
		*y_off_u = -all->a;
		all->a = 0;
	}
	*offset_y = all->a;
	if (all->a >= (int)all->map_height - 32 && all->map_height > 32)
		all->a = (int)all->map_height - 32;
	if (*offset_y > (int)all->map_height - 32 && all->map_height > 32)
		*offset_y = (int)all->map_height - 32;
}

void	minimap_init_x(t_all *all, int *off_x, int *x_off_l, int *player_dist)
{
	*off_x = 0;
	all->b = (int)round(all->x) - 16;
	if (all->b < 0)
	{
		*x_off_l = -all->b;
		all->b = 0;
	}
	if (all->b + 16 > (int)all->map_width - 16 && all->map_width > 32)
		all->b = (int)all->map_width - 32;
	*off_x = all->b;
	if (*off_x >= (int)all->map_width - 32 && all->map_width > 32)
		*off_x = (int)all->map_width - 32;
	if (((int)round(all->x) + *player_dist) > (int)all->map_width)
		*player_dist = -((int)round(all->x) - (int)all->map_width);
}

void	draw_minimap_2(t_all *all, int y_off_u, int x_off_l, int player_dist)
{
	int	start_off_y;
	int	start_off_x;

	update_player_pos(all);
	minimap_init_y(all, &start_off_y, &y_off_u);
	while (all->a < (int)round(all->y) + 16
		+ y_off_u && all->a < (int)all->map_height)
	{
		minimap_init_x(all, &start_off_x, &x_off_l, &player_dist);
		while (all->b < (int)round(all->x) + player_dist
			+ x_off_l && all->b < (int)all->map_width)
		{
			if (all->map[all->a][all->b] == 0 || all->map[all->a][all->b] == 2)
				paint_map(all, start_off_x, start_off_y, 0xffffffff);
			else if (all->map[all->a][all->b] == 1)
				paint_map(all, start_off_x, start_off_y, 0x000000ff);
			if (all->map[all->a][all->b] == 2)
				paint_map_player(all, start_off_x, start_off_y);
			all->b++;
		}
		all->a++;
	}
	draw_ray_minimap(all, start_off_y, start_off_x);
}
