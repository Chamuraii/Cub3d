/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:19:30 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/29 22:19:38 by jorgfern         ###   ########.fr       */
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
	free(all->WE_texture);
	free(all->EA_texture);
	free(all->SO_texture);
	free(all->NO_texture);
	free(all->north);
	free(all->east);
	free(all->south);
	free(all->west);
	free(all->gun);
	free(all->next_line);
}

/* FT_EXIT : closes program and display given message */

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
		ft_printf("%s\n", "Error\n- FAILED OPENING MAP FILE -\n");
	else if (status == 6)
		ft_printf("%s\n", "Error\n- NOT A MAP -\n");
	else if (status == 7)
		ft_printf("%s\n", "Error\n- INVALID ARGUMENTS -\n");
}

void	ft_exit(t_all *all, int status)
{
	get_reason(status);
	if (all->mlx)
		mlx_terminate(all->mlx);
	ft_free(all);
	exit(status);
}
