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
	while (all->ray_hits[i][0] != -1)
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

void	draw_minimap(t_all *all)
{
	int	y_offset_u;
	int	x_offset_l;
	int	player_dist;

	y_offset_u = 0;
	x_offset_l = 0;
	player_dist = 16;
	draw_minimap_2(all, y_offset_u, x_offset_l, player_dist);
}
