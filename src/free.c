/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:19:30 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/29 22:19:38 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_map_free(t_all *all)
{
	int i;

	i = 0;
	while (i < all->map_height)
	{
		free(all->map[i]);
		free(all->map_char[i]);
		free(all->map_cpy[i]);
	}
	free(all->map);
	free(all->map_char);
	free(all->map_cpy);
}

void	ft_free(t_all *all)
{
	ft_map_free(all);
}