/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:19:24 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:45:36 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_validator_2(t_all *all, char **str, int i)
{
	while (ft_isspace(str[0][i]))
		++i;
	if (!str[0][i])
		ft_exit(all, 4);
}

void	map_validator_3(t_all *all, char ***matrix, int i, int j)
{
	if (!all->y || !all->x)
		ft_exit(all, 4);
	(*matrix)[j] = 0;
	all->map_height = j;
	all->map_cpy = map_copy(all, matrix, j);
	all->map_char = map_copy(all, matrix, j);
	i = -1;
	while ((*matrix)[++i])
		free((*matrix)[i]);
	flood_fill(all, all->map_cpy, (int)all->y, (int)all->x);
	flood_validator(all, all->map_cpy);
}

void	set_player(t_all *all, char **str, int i, int j)
{
	if (ft_strchr("NESW", str[0][i]))
	{
		if (all->player_count)
			ft_exit(all, 4);
		if (str[0][i] == 'N')
			all->z = 271;
		else if (str[0][i] == 'W')
			all->z = 1;
		else if (str[0][i] == 'S')
			all->z = 91;
		else if (str[0][i] == 'E')
			all->z = 181;
		all->y = j + 0.1;
		all->x = i + 0.1;
		all->oldy = j;
		all->oldx = i;
		all->player_count = 1;
	}
}

int	map_validator(t_all *all, char **str, int fd)
{
	int		i;
	int		j;
	char	**matrix;

	j = ft_strlen(*str);
	*str = ft_strjoin(*str, ft_strdup("\n"));
	while (j < (int)ft_strlen(*str))
	{
		j = ft_strlen(*str);
		*str = ft_strjoin(*str, get_next_line(fd));
	}
	matrix = ft_split(*str, '\n');
	i = 0;
	while (matrix[i])
	{
		j = 0;
		map_validator_2(all, &(matrix[i]), j);
		while (matrix[i][j])
		{
			if (!ft_strchr("01NESW", matrix[i][j]) && !ft_isspace(matrix[i][j]))
				ft_exit(all, 4);
			set_player(all, &(matrix[i]), j, i);
			++j;
		}
		if (j > (int)all->map_width)
			all->map_width = j;
		++i;
	}
	map_validator_3(all, &matrix, j, i);
	return (1);
}
