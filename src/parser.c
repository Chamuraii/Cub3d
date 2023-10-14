/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:52:34 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/28 15:08:22 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parser_init(t_all *all)
{
	all->mlx = 0;
	all->map_cpy = 0;
	all->map_char = 0;
	all->map = 0;
	all->NO_texture = 0;
	all->SO_texture = 0;
	all->WE_texture = 0;
	all->EA_texture = 0;
	all->north = 0;
	all->east = 0;
	all->south = 0;
	all->west = 0;
	all->gun = 0;
	all->ceiling_color_rgb[0] = 256;
	all->ceiling_color_rgb[1] = 256;
	all->ceiling_color_rgb[2] = 256;
	all->ceiling_color_rgb[3] = 0;
	all->floor_color_rgb[0] = 256;
	all->floor_color_rgb[1] = 256;
	all->floor_color_rgb[2] = 256;
	all->floor_color_rgb[3] = 0;
	all->map_width = 0;
	all->map_height = 0;
	all->x = 0;
	all->y = 0;
	all->oldchar = 0;
	all->ray_num = 0;
	all->texture_counter = 0;
	all->gun_img = 0;
	all->gun_bool = 0;
	all->i = 0;
	all->j = 0;
	all->mouse_counter = 0;
	all->mouse_flag = 0;
	all->next_line = 0;
	all->is_there_map = 0;
}

void parser_setter(t_all *all)
{
	all->floor_color = get_rgba(all->floor_color_rgb[0], all->floor_color_rgb[1], all->floor_color_rgb[2], 255);
	all->ceiling_color = get_rgba(all->ceiling_color_rgb[0], all->ceiling_color_rgb[1], all->ceiling_color_rgb[2], 255);
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
	char	*ext;
	int		j;

	j = 2;
	while (ft_isspace(str[j]))
		++j;
	if (j == 2)
		ft_exit(all, 2);
	ext = ft_strrchr(str, '.');
	if ((!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "EA", 2)) && !ft_strcmp(ext, ".png"))
	{
		if (step == 0)
		{
			if (all->NO_texture)
				ft_exit(all, 3);
			all->NO_texture = ft_strdup(str + j);
		}
		else if (step == 1)
		{
			if (all->SO_texture)
				ft_exit(all, 3);
			all->SO_texture = ft_strdup(str + j);
		}
		else if (step == 2)
		{
			if (all->WE_texture)
				ft_exit(all, 3);
			all->WE_texture = ft_strdup(str + j);
		}
		else if (step == 3)
		{
			if (all->EA_texture)
				ft_exit(all, 3);
			all->EA_texture = ft_strdup(str + j);
		}
	}
	else
		ft_exit(all, 3);
	return (1);
}

int	rgb_repeated_checker(t_all *all, int boole)
{
	int i;

	if (!boole)
	{
		if (all->floor_color_rgb[3]) {
			ft_exit(all, 3);
		}
		all->floor_color_rgb[3] = 1;
	}
	else if (boole == 1)
	{
		if (all->ceiling_color_rgb[3]) {
			ft_exit(all, 3);
		}
		all->ceiling_color_rgb[3] = 1;
	}
	i = -1;
	if (boole == 3)
		while (++i < 3)
			if (all->floor_color_rgb[i] >= 256 ||
				all->ceiling_color_rgb[i] >= 256)
				ft_exit(all, 3);
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
		ft_exit(all, 3);
	j = 0;
	comma_counter = 0;
	while (str[i])
	{
		if (boole == 0)
			all->floor_color_rgb[j++] = (ft_atoi(str + i) % 256);
		else
			all->ceiling_color_rgb[j++] = (ft_atoi(str + i) % 256);
		while (ft_isdigit(str[i]))
			++i;
		if (str[i] == ',')
			++comma_counter;
		else if (str[i])
			ft_exit(all, 3);
		if (!str[i++] && comma_counter != 2)
			ft_exit(all, 3);
	}
	rgb_repeated_checker(all, boole);
	return (1);
}

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

char	**map_copy(t_all *all, char **matrix, int height)
{
	int		i;
	char	**map_cpy;

	i = 0;
	map_cpy = ft_calloc((height + 1) * sizeof(char *), 1);
	if (!map_cpy)
		ft_exit(all, 1);
	while (i < height)
	{
		map_cpy[i] = ft_strdup(matrix[i]);
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

void	flood_fill(t_all *all, char **map, int y, int x)
{
	if (x < 0 || x == all->map_width || y < 0 || y == all->map_height || map[y][x] == '1' || map[y][x] == 'F')
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
			ft_exit(all, 4);
		i = 0;
		while (str[0][i])
		{
			if (str[0][i] != '0' && str[0][i] != '1' && str[0][i] != 'N' && str[0][i] != 'S' && str[0][i] != 'E' && str[0][i] != 'W' && str[0][i] != 'D' && !ft_isspace(str[0][i]))
				ft_exit(all, 4);
			if (str[0][i] == 'N' || str[0][i] == 'W' || str[0][i] == 'S' || str[0][i] == 'E')
			{
				if (player_count)
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
		ft_exit(all, 4);
	matrix[j] = 0;
	if (i > all->map_height)
		all->map_height = j;
	all->map_cpy = map_copy(all, matrix, j);
	all->map_char = map_copy(all, matrix, j);
	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	flood_fill(all, all->map_cpy, (int)all->y, (int)all->x);
	flood_validator(all, all->map_cpy);
	return (1);
}

int	cub_line_validator(t_all *all, char **str, int fd)
{
	if (cub_directions_validator(all, *str) == 2)
	{
		if (!ft_strncmp(*str, "F", 1))
			rgb_validator(all, *str, 0);
		else if (!ft_strncmp(*str, "C", 1))
			rgb_validator(all, *str, 1);
		else
			map_validator(all, str, fd);
	}
	return (1);
}

int	cub_validator(t_all *all, char **argv, int fd, char **str)
{
	int	i;

	fd = open(argv[1], 0);
	if (fd < 0)
		ft_exit(all, 5);
	*str = get_next_line_no_nl(fd);
	i = 0;
	if (!(*str))
		ft_exit(all, 3);
	while (*str)
	{
		if (!str[0][0])
		{
			free(*str);
			*str = get_next_line_no_nl(fd);
			continue ;
		}
		cub_line_validator(all, str, fd);
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
	all->map = ft_calloc(all->map_height * all->map_width * 4, 1);
	if (!all->map)
		ft_exit(all, 1);
	while (all->map_char[i])
	{
		all->map[i] = ft_calloc(all->map_width * 4, 1);
		if (!all->map[i])
			ft_exit(all, 1);
		j = 0;
		while (all->map_char[i][j])
		{
			if (all->map_char[i][j] == '0' || all->map_char[i][j] == ' ')
				all->map[i][j] = 0;
			else if (all->map_char[i][j] == '1')
				all->map[i][j] = 1;
			else if (all->map_char[i][j] == 'N' || all->map_char[i][j] == 'W' || all->map_char[i][j] == 'S' || all->map_char[i][j] == 'E')
				all->map[i][j] = 2;
			else
				all->map[i][j] = 3;
			++j;
		}
		++i;
	}
}

int	main_validator(t_all *all, char **argv, int argc)
{
	int		fd;

	if (argc != 2)
		ft_exit(all, 7);
	fd = 0;
	if (!ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
		cub_validator(all, argv, fd, &(all->next_line));
	else
		ft_exit(all, 6);
	rgb_repeated_checker(all, 3);
	if (!all->is_there_map)
		ft_exit(all, 3);
	parse_map(all);
	parser_setter(all);
	return (1);
}
