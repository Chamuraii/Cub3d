/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:52:34 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/29 21:40:32 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parser_init(t_all *all)
{
	all->NO_texture = 0;
	all->SO_texture = 0;
	all->WE_texture = 0;
	all->EA_texture = 0;
	all->ceiling_color[0] = 0;
	all->ceiling_color[1] = 0;
	all->ceiling_color[2] = 0;
	all->ceiling_color[3] = 0;
	all->floor_color[0] = 0;
	all->floor_color[1] = 0;
	all->floor_color[2] = 0;
	all->floor_color[3] = 0;
	all->map_width = 0;
	all->map_height = 0;
	all->x = 0;
	all->y = 0;
}

char	*get_next_line_no_nl(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (str)
		if (str[0])
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
	return (str);
}

int	texture_map_validator(t_all *all, char *str, int step)
{
	int	i;
	int	j;

	j = 2;
	while (ft_isspace(str[j]))
		++j;
	if (j == 2)
		return (0);
	i = ft_strlen(str);
	if (i >= 5 + j)
		while (--i > 0)
			if (str[i] == '.')
				break ;
	if (i > 5 + j && (!ft_strcmp(str + i, ".png") || !ft_strcmp(str + i, ".xmp")))
	{
		if (step == 0)
		{
			if (all->NO_texture)
				return (0);
			all->NO_texture = ft_strdup(str + j);
		}
		else if (step == 1)
		{
			if (all->SO_texture)
				return (0);
			all->SO_texture = ft_strdup(str + j);
		}
		else if (step == 2)
		{
			if (all->WE_texture)
				return (0);
			all->WE_texture = ft_strdup(str + j);
		}
		else if (step == 3)
		{
			if (all->EA_texture)
				return (0);
			all->EA_texture = ft_strdup(str + j);
		}
	}
	else
		return (0);
	return (1);
}

int	rgb_repeated_checker(t_all *all, int boole)
{
	if (boole == 0)
	{
		if (all->floor_color[3])
			return (0);
		all->floor_color[3] = 1;
	}
	else
	{
		if (all->ceiling_color[3])
			return (0);
		all->ceiling_color[3] = 1;
	}
	return (1);
}

int	rgb_validator(t_all *all, char *str, int boole)
{
	int	i;
	int	j;
	int	comma_counter;

	i = 1;
	while (ft_isspace(str[i]))
		++i;
	if (i == 1)
		return (0);
	j = 0;
	comma_counter = 0;
	while (str[i])
	{
		if (boole == 0)
			all->floor_color[j++] = ft_atoi(str + i);
		else
			all->ceiling_color[j++] = ft_atoi(str + i);
		while (str[i] && ft_isdigit(str[i]))
			++i;
		if (str[i] == ',')
			++comma_counter;
		else if (str[i])
			return (0);
		if (!str[i++] && comma_counter != 2)
			return (0);
	}
	if (!rgb_repeated_checker(all, boole))
		return (0);
	return (1);
}

int	cub_directions_validator(t_all *all, char *str)
{
	if (!ft_strncmp(str, "NO", 2))
	{
		if (!texture_map_validator(all, str, 0))
			return (0);
	}
	else if (!ft_strncmp(str, "SO", 2))
	{
		if (!texture_map_validator(all, str, 1))
			return (0);
	}
	else if (!ft_strncmp(str, "WE", 2))
	{
		if (!texture_map_validator(all, str, 2))
			return (0);
	}
	else if (!ft_strncmp(str, "EA", 2))
	{
		if (!texture_map_validator(all, str, 3))
			return (0);
	}
	else
		return (2);
	return (1);
}

char	**map_copy(t_all *all, char **matrix, int height)
{
	int		i;
	char	**map_cpy;

	i = 0;
	map_cpy = malloc((height + 1) * sizeof(char *));
	while (i < height)
	{
		map_cpy[i] = ft_strdup(matrix[i]);
		while (ft_strlen(map_cpy[i]) != all->map_width)
			map_cpy[i] = ft_strjoin(map_cpy[i], ft_strdup(" "));
		++i;
	}
	map_cpy[i] = 0;
	return (map_cpy);
}

void	flood_fill(t_all *all, char **map, int y, int x)
{
	if (x == 0 || x == all->map_width || y == 0 || y == all->map_height - 1 || map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(all, map, y + 1, x);
	flood_fill(all, map, y - 1, x);
	flood_fill(all, map, y, x + 1);
	flood_fill(all, map, y, x - 1);
}

int	flood_validator(t_all *all,char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
		if (map[i][j++] == 'F')
			return (0);
	i = all->map_height - 1;
	j = 0;
	while (map[i][j])
		if (map[i][j++] == 'F')
			return (0);
	i = 0;
	j = 0;
	while (map[i])
		if (map[i++][j] == 'F')
			return (0);
	i = 0;
	j = all->map_width - 1;
	while (map[i])
		if (map[i++][j] == 'F')
			return (0);
	return (1);
}

int	map_validator(t_all *all, char **str, int fd)
{
	int		i;
	int		j;
	int		player_count;
	char	*matrix[1024];

	player_count = 0;
	j = 0;
	while (*str)
	{
		i = 0;
		while (ft_isspace(str[0][i]))
			++i;
		if (!str[0][i])
			return (0);
		i = 0;
		while (str[0][i])
		{
			if (str[0][i] != '0' && str[0][i] != '1' && str[0][i] != 'N' && str[0][i] != 'D' && !ft_isspace(str[0][i]))
				return (0);
			if (str[0][i] == 'N')
			{
				if (player_count)
					return (0);
				all->y = j;
				all->x = i;
				player_count = 1;
			}
			++i;
		}
		if (i > all->map_width)
			all->map_width = i;
		matrix[j++] = ft_strdup(*str);
		free(*str);
		*str = get_next_line_no_nl(fd);
	}
	if (!all->y || !all->x)
		return (0);
	matrix[j] = 0;
	if (i > all->map_height)
		all->map_height = j;
	all->map_cpy = map_copy(all, matrix, j);
	all->map_char = map_copy(all, matrix, j);
	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	flood_fill(all, all->map_cpy, all->y, all->x);
	if (!flood_validator(all, all->map_cpy))
		return (0);
	return (1);
}

int	cub_line_validator(t_all *all, char **str, int fd)
{
	int	save;

	save = cub_directions_validator(all, *str);
	if (!save)
		return (0);
	else if (save == 2)
	{
		if (!ft_strncmp(*str, "F", 1))
		{
			if (!rgb_validator(all, *str, 0))
				return (0);
		}
		else if (!ft_strncmp(*str, "C", 1))
		{
			if (!rgb_validator(all, *str, 1))
				return (0);
		}
		else
			if (!map_validator(all, str, fd))
				return (0);
	}
	return (1);
}

int	cub_validator(t_all *all, char **argv, int fd, char **str)
{
	int	i;

	fd = open(argv[1], 0);
	if (fd < 0)
		return (0);
	*str = get_next_line_no_nl(fd);
	i = 0;
	while (*str)
	{
		if (!str[0][0])
		{
			free(*str);
			*str = get_next_line_no_nl(fd);
			continue ;
		}
		if (!cub_line_validator(all, str, fd))
			return (free(*str), 0);
		free(*str);
		*str = get_next_line_no_nl(fd);
		++i;
	}
	free(*str);
	close(fd);
	return (1);
}

void	parse_map(t_all *all)
{
	int	i;
	int j;

	i = 0;
	all->map = malloc(all->map_height * all->map_width * 4);
	while (all->map_char[i])
	{
		all->map[i] = malloc(all->map_width * 4);
		j = 0;
		while (all->map_char[i][j])
		{
			if (all->map_char[i][j] == '0' || all->map_char[i][j] == ' ')
				all->map[i][j] = 0;
			else if (all->map_char[i][j] == '1')
				all->map[i][j] = 1;
			else if (all->map_char[i][j] == 'N')
				all->map[i][j] = 2;
			else
				all->map[i][j] = 3;
			++j;
		}
		++i;
	}
}

int	main_validator(t_all *all, char **argv)
{
	int		i;
	int		fd;
	char	*str;

	str = 0;
	fd = 0;
	i = ft_strlen(argv[1]);
	if (i >= 5)
		while (--i > 0)
			if (argv[1][i] == '.')
				break ;
	if (i > 0 && !ft_strcmp(argv[1] + i, ".cub"))
	{
		if (!cub_validator(all, argv, fd, &str))
			return (0);
	}
	else
		return (0);
	parse_map(all);
	return (1);
}
