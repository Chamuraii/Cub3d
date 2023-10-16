/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:15:29 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/16 13:38:51 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cub_directions_validator(t_all *all, char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		texture_map_validator(all, str, 0);
	else if (!ft_strncmp(str, "SO", 2))
		texture_map_validator(all, str, 1);
	else if (!ft_strncmp(str, "WE", 2))
		texture_map_validator(all, str, 2);
	else if (!ft_strncmp(str, "EA", 2))
		texture_map_validator(all, str, 3);
	else
		return (2);
	return (1);
}

void	texture_map_check(t_all *all, int step, char *str, int j)
{
	if (step == 0)
	{
		if (all->no_texture)
			ft_exit(all, 3);
		all->no_texture = ft_strdup(str + j);
	}
	else if (step == 1)
	{
		if (all->so_texture)
			ft_exit(all, 3);
		all->so_texture = ft_strdup(str + j);
	}
	else if (step == 2)
	{
		if (all->we_texture)
			ft_exit(all, 3);
		all->we_texture = ft_strdup(str + j);
	}
	else if (step == 3)
	{
		if (all->ea_texture)
			ft_exit(all, 3);
		all->ea_texture = ft_strdup(str + j);
	}
}

int	texture_map_validator(t_all *all, char *str, int step)
{
	char	*ext;
	int		j;

	j = 2;
	while (ft_isspace(str[j]))
		++j;
	if (j == 2)
		ft_exit(all, 2);
	ext = ft_strrchr(str, '.');
	if ((!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "WE", 2)
			|| !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "EA", 2))
		&& !ft_strcmp(ext, ".png"))
	{
		texture_map_check(all, step, str, j);
	}
	else
		ft_exit(all, 3);
	return (1);
}

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
