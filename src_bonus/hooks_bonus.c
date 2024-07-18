/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:48:43 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:48:46 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_key_hook(struct mlx_key_data keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_L)
	{
		if (all->mouse_flag)
		{
			all->mouse_flag = 0;
			mlx_set_cursor_mode(all->mlx, MLX_MOUSE_NORMAL); // Function not working
			return ;
		}
		if (!all->mouse_flag)
			all->mouse_flag = 1;
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(all->mlx, WIDTH / 2, HEIGHT / 2);
	}
}

void	mouse(t_all *all)
{
	if (all->mouse_flag)
	{
		if (all->mouse_counter >= 3)
		{
			mlx_set_mouse_pos(all->mlx, WIDTH / 2, HEIGHT / 2); // Function not working
			all->mouse_counter = 0;
		}
		++(all->mouse_counter);
		mlx_get_mouse_pos(all->mlx, &(all->mouse_x_pos), &(all->mouse_y_pos));
		all->z = good_angles(all->z
				- ((all->mouse_x_pos - (WIDTH / 2)) / 10));
	}
	if (mlx_is_mouse_down(all->mlx, MLX_MOUSE_BUTTON_LEFT))
		all->gun_bool = 1;
	if (all->gun_bool)
		gun(all);
}
