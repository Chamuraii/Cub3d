/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:12 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:44:32 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rgb_repeated_checker(t_all *all, int boole)
{
	int	i;

	if (!boole)
	{
		if (all->floor_color_rgb[3])
			ft_exit(all, 3);
		all->floor_color_rgb[3] = 1;
	}
	else if (boole == 1)
	{
		if (all->ceiling_color_rgb[3])
			ft_exit(all, 3);
		all->ceiling_color_rgb[3] = 1;
	}
	i = -1;
	if (boole == 3)
		while (++i < 3)
			if (all->floor_color_rgb[i] >= 256
				|| all->ceiling_color_rgb[i] >= 256)
				ft_exit(all, 3);
	return (1);
}

int	rgb_validate_coma(char *str, int *comma_counter, int i)
{
	if (str[i] == ',' && *comma_counter < 2)
	{
		++(*comma_counter);
		return (1);
	}
	else if (str[i] || (*comma_counter > 2
			|| (*comma_counter < 2 && !str[i])))
		return (0);
	return (1);
}

void	rgb_validator(t_all *all, char *str, int boole)
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
		if (!boole)
			all->floor_color_rgb[j++] = ft_atoi(str + i);
		else
			all->ceiling_color_rgb[j++] = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			++i;
		if (!rgb_validate_coma(str, &comma_counter, i++))
			ft_exit(all, 3);
	}
	rgb_repeated_checker(all, boole);
}
