/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:24:47 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/15 18:13:14 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_all	all;

	parser_init(&all);
	if (!main_validator(&all, argv, argc))
		ft_exit(&all, -1);
	if (!get_textures(&all))
		ft_exit(&all, 2);
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
