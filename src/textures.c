/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:02:21 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:24:43 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_textures(t_all *all)
{
	if (!all->no_texture || !all->ea_texture
		|| !all->so_texture || !all->we_texture)
		ft_exit(all, 3);
	all->north = mlx_load_png(all->no_texture);
	if (!all->north)
		return (0);
	all->east = mlx_load_png(all->ea_texture);
	if (!all->east)
		return (0);
	all->south = mlx_load_png(all->so_texture);
	if (!all->south)
		return (0);
	all->west = mlx_load_png(all->we_texture);
	if (!all->west)
		return (0);
	return (1);
}
