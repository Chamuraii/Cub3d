/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:12:54 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:44:41 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_minimap(t_all *all)
{
	int	y_offset_u;
	int	x_offset_l;
	int	player_dist;

	y_offset_u = 0;
	x_offset_l = 0;
	player_dist = 16;
	draw_minimap_2(all, y_offset_u, x_offset_l, player_dist);
}
