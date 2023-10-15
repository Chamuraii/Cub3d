/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:23:23 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:25:47 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	gun3(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 0;
	up[1] = 378;
	down[0] = 330;
	down[1] = 342;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 336, HEIGHT - 338);
	++(*counter);
}

void	gun4(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 470;
	up[1] = 349;
	down[0] = 309;
	down[1] = 371;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 350);
	++(*counter);
}

void	gun5(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 903;
	up[1] = 365;
	down[0] = 370;
	down[1] = 355;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 350);
	++(*counter);
}

void	gun6(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	all->gun_bool = 0;
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 0;
	up[1] = 0;
	down[0] = 276;
	down[1] = 265;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
	*counter = 0;
}
