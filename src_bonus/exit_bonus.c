/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:19:30 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/16 13:35:25 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_map_free(t_all *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->map_height)
	{
		if (all->map_cpy)
			free(all->map_cpy[i]);
		if (all->map_char)
			free(all->map_char[i]);
		if (all->map)
			free(all->map[i]);
		++i;
	}
	free(all->map_cpy);
	free(all->map_char);
	free(all->map);
}

void	ft_free(t_all *all)
{
	ft_map_free(all);
	free(all->we_texture);
	free(all->ea_texture);
	free(all->so_texture);
	free(all->no_texture);
	free(all->next_line);
}

void	get_reason(int status)
{
	if (!status)
		ft_printf("%s\n", "Bye <3");
	else if (status == -1)
		ft_printf("%s\n", "Error\n- MLX PROBLEM -");
	else if (status == 1)
		ft_printf("%s\n", "Error\n- OUT OF MEMORY -");
	else if (status == 2)
		ft_printf("%s\n", "Error\n- MLX COULD NOT LOAD TEXTURE -");
	else if (status == 3)
		ft_printf("%s\n", "Error\n- INVALID MAP CONFIGURATION -");
	else if (status == 4)
		ft_printf("%s\n", "Error\n- INVALID MAP -");
	else if (status == 5)
		ft_printf("%s\n", "Error\n- FAILED OPENING MAP FILE -");
	else if (status == 6)
		ft_printf("%s\n", "Error\n- NOT A MAP -");
	else if (status == 7)
		ft_printf("%s\n", "Error\n- INVALID ARGUMENTS -");
}

void	ft_exit(t_all *all, int status)
{
	get_reason(status);
	if (all->mlx)
		mlx_terminate(all->mlx);
	ft_free(all);
	exit(status);
}
