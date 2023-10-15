# include "../include/cub3d.h"

void	map_validator_2(t_all *all, char **str, int i)
{
	while (ft_isspace(str[0][i]))
		++i;
	if (!str[0][i])
		ft_exit(all, 4);
}

void	map_validator_3(t_all *all, char *matrix[][1024], int i, int j)
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
	char	*matrix[1024];

	j = 0;
	while (*str)
	{
		i = 0;
		map_validator_2(all, str, i);
		while (str[0][i])
		{
			if (!ft_strchr("01NESW", str[0][i]) && !ft_isspace(str[0][i]))
				ft_exit(all, 4);
			set_player(all, str, i, j);
			++i;
		}
		if (i > (int)all->map_width)
			all->map_width = i;
		*str = get_line_map(&matrix, str, fd, &j);
	}
	map_validator_3(all, &matrix, i, j);
	return (1);
}
