/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:38 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:46:21 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(t_all *all, char **map, int y, int x)
{
	if (x < 0 || x == (int)all->map_width
		|| y < 0 || y == (int)all->map_height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(all, map, y + 1, x);
	flood_fill(all, map, y - 1, x);
	flood_fill(all, map, y, x + 1);
	flood_fill(all, map, y, x - 1);
}

int	flood_validator(t_all *all, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
		if (map[i][j++] == 'F')
			ft_exit(all, 4);
	i = (int)all->map_height - 1;
	j = 0;
	while (map[i][j])
		if (map[i][j++] == 'F')
			ft_exit(all, 4);
	i = 0;
	j = 0;
	while (map[i])
		if (map[i++][j] == 'F')
			ft_exit(all, 4);
	i = 0;
	j = (int)all->map_width - 1;
	while (map[i])
		if (map[i++][j] == 'F')
			ft_exit(all, 4);
	return (1);
}

char	**map_copy(t_all *all, char ***matrix, int height)
{
	int		i;
	char	**map_cpy;

	i = 0;
	map_cpy = ft_calloc((height + 1) * sizeof(char *), 1);
	if (!map_cpy)
		ft_exit(all, 1);
	while (i < height)
	{
		map_cpy[i] = ft_strdup((*matrix)[i]);
		if (!map_cpy[i])
			ft_exit(all, 1);
		while (ft_strlen(map_cpy[i]) != all->map_width)
		{
			map_cpy[i] = ft_strjoin(map_cpy[i], ft_strdup(" "));
			if (!map_cpy[i])
				ft_exit(all, 1);
		}
		++i;
	}
	map_cpy[i] = 0;
	all->is_there_map = 1;
	return (map_cpy);
}
