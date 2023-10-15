/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:24:08 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:44:09 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	start_gun(t_all *all)
{
	uint32_t	up_left_point[2];
	uint32_t	down_right_point[2];

	all->gun = mlx_load_png("textures/myguns.png");
	if (!all->gun)
		ft_exit(all, 2);
	up_left_point[0] = 0;
	up_left_point[1] = 0;
	down_right_point[0] = 276;
	down_right_point[1] = 265;
	all->gun_img = mlx_texture_area_to_image(all->mlx,
			all->gun, up_left_point, down_right_point);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
}

void	gun(t_all *all)
{
	static int	counter;
	uint32_t	up_left_point[2];
	uint32_t	down_right_point[2];

	if (counter < 2)
		gun1(all, up_left_point, down_right_point, &counter);
	else if (counter < 4)
		gun2(all, up_left_point, down_right_point, &counter);
	else if (counter < 6)
		gun3(all, up_left_point, down_right_point, &counter);
	else if (counter < 12)
		gun4(all, up_left_point, down_right_point, &counter);
	else if (counter < 18)
		gun5(all, up_left_point, down_right_point, &counter);
	else if (counter == 18)
		gun6(all, up_left_point, down_right_point, &counter);
}

void	gun1(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 464;
	up[1] = 0;
	down[0] = 276;
	down[1] = 265;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 276, HEIGHT - 265);
	++(*counter);
}

void	gun2(t_all *all, uint32_t *up, uint32_t *down, int *counter)
{
	mlx_delete_image(all->mlx, all->gun_img);
	up[0] = 879;
	up[1] = 0;
	down[0] = 298;
	down[1] = 323;
	all->gun_img = mlx_texture_area_to_image(all->mlx, all->gun, up, down);
	mlx_image_to_window(all->mlx, all->gun_img, WIDTH - 300, HEIGHT - 300);
	++(*counter);
}
