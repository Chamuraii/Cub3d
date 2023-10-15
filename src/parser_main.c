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
	int	j;

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
			else if (ft_strchr("NESW", all->map_char[i][j]))
				all->map[i][j] = 2;
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
	all->next_line = 0;
	return (1);
}
