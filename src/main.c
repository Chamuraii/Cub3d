/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/14 20:53:49 by jorgfern         ###   ########.fr       */
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
			mlx_set_cursor_mode(all->mlx, MLX_MOUSE_NORMAL);
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
		if (all->mouse_counter == 3)
		{
			mlx_set_mouse_pos(all->mlx, WIDTH / 2, HEIGHT / 2);
			all->mouse_counter = 0;
		}
		++(all->mouse_counter);
		mlx_get_mouse_pos(all->mlx, &(all->mouse_x_pos), &(all->mouse_y_pos));
		all->z = good_angles(all, all->z
				- ((all->mouse_x_pos - (WIDTH / 2)) / 10));
	}
	if (mlx_is_mouse_down(all->mlx, MLX_MOUSE_BUTTON_LEFT))
		all->gun_bool = 1;
	if (all->gun_bool)
		gun(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	parser_init(&all);
	if (!main_validator(&all, argv, argc))
		ft_exit(&all, -1);
	ft_printf ("Map validation successful!\n");
	if (!get_textures(&all))
		ft_exit(&all, 2);
	else
		ft_printf ("Texture validation successful!\n");
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	if (!all.mlx)
		ft_exit(&all, -1);
	mlx_set_window_title(all.mlx, "Cub3d");
	all.background = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all.mlx, all.background, 0, 0);
	rays(&all);
	start_gun(&all);
	mlx_key_hook(all.mlx, &my_key_hook, ((void *)&all));
	mlx_loop_hook(all.mlx, my_hook, ((void *)&all));
	mlx_loop(all.mlx);
	ft_exit(&all, 0);
}
