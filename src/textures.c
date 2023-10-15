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
	if (!all->NO_texture || !all->EA_texture
		|| !all->SO_texture || !all->WE_texture)
		ft_exit(all, 3);
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
