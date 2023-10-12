/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:02:21 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/08 22:02:33 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_textures(t_all *all)
{
	all->north = mlx_load_png(all->NO_texture);
	if (!all->north)
		return (0);
	all->east = mlx_load_png(all->EA_texture);
	if (!all->east)
		return (0);
	all->south = mlx_load_png(all->SO_texture);
	if (!all->south)
		return (0);
	all->west = mlx_load_png(all->WE_texture);
	if (!all->west)
		return (0);
	return (1);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int get_rgba_img(uint8_t *pixels, unsigned int width, unsigned int y, double x)
{
	return ((((pixels[(int) (((y * (width)) + (int)round(x))) * 4]) << 24)) |
			((pixels[(int) (((y * (width)) + (int)round(x))) * 4 + 1]) << 16) |
			((pixels[(int) ((y * (width)) + (int)round(x)) * 4 + 2] << 8)) |
			((pixels[(int) ((y * (width)) + (int)round(x)) * 4 + 3])));
}

unsigned int get_pixel_color(t_all *all, double range) {

	mlx_texture_t *texture;
	double x;
	double scale_y;
	int y;

	texture = all->side;
	scale_y =  (double)texture->height / range;
	if (range > HEIGHT && !all->texture_counter)
		all->texture_counter = (unsigned int)((round(range) - HEIGHT) / 2);
	y = (int)((all->texture_counter++ * scale_y));
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
	return (get_rgba_img(texture->pixels, texture->width, y, x));
}

void	start_gun(t_all *all)
{
	uint32_t up_left_point[2];
	uint32_t down_right_point[2];

	all->gun[0] = mlx_load_png("textures/myguns.png");
	up_left_point[0] = 0;
	up_left_point[1] = 0;
	down_right_point[0] = 276;
	down_right_point[1] = 265;
	all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
}

void	gun(t_all *all)
{
	static int tumae;
	uint32_t up_left_point[2];
	uint32_t down_right_point[2];

	if (tumae < 2)
	{
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 464;
		up_left_point[1] = 0;
		down_right_point[0] = 276;
		down_right_point[1] = 265;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
		++tumae;
	}
	else if (tumae < 4)
	{
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 879;
		up_left_point[1] = 0;
		down_right_point[0] = 298	;
		down_right_point[1] = 323;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 300);
		++tumae;
	}
	else if (tumae < 6)
	{
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 0;
		up_left_point[1] = 378;
		down_right_point[0] = 330;
		down_right_point[1] = 342;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 336, HEIGHT - 338);
		++tumae;
	}
	else if (tumae < 12)
	{
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 470;
		up_left_point[1] = 349;
		down_right_point[0] = 309;
		down_right_point[1] = 371;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 350);
		++tumae;
	}
	else if (tumae < 18)
	{
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 903;
		up_left_point[1] = 365;
		down_right_point[0] = 370;
		down_right_point[1] = 355;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 350);
		++tumae;
	}
	else if (tumae == 18)
	{
		tumae = 0;
		all->gun_bool = 0;
		mlx_delete_image(all->mlx,all->gun_img);
		up_left_point[0] = 0;
		up_left_point[1] = 0;
		down_right_point[0] = 276;
		down_right_point[1] = 265;
		all->gun_img =  mlx_texture_area_to_image(all->mlx, all->gun[0], up_left_point, down_right_point);
		mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
	}
}