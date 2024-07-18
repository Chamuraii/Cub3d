/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:13:50 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:46:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parser_init_2(t_all *all)
{
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
	all->mouse_counter = 0;
	all->mouse_flag = 0;
	all->next_line = 0;
	all->is_there_map = 0;
	all->player_count = 0;
}

void	parser_init(t_all *all)
{
	all->mlx = 0;
	all->map_cpy = 0;
	all->map_char = 0;
	all->map = 0;
	all->no_texture = 0;
	all->so_texture = 0;
	all->we_texture = 0;
	all->ea_texture = 0;
	all->north = 0;
	all->east = 0;
	all->south = 0;
	all->west = 0;
	all->gun = 0;
	all->ceiling_color_rgb[0] = 256;
	all->ceiling_color_rgb[1] = 256;
	all->ceiling_color_rgb[2] = 256;
	all->angle_change = (double)FOV / (double)WIDTH;
	parser_init_2(all);
}

void	parser_setter(t_all *all)
{
	all->floor_color = get_rgba(all->floor_color_rgb[0],
			all->floor_color_rgb[1], all->floor_color_rgb[2], 255);
	all->ceiling_color = get_rgba(all->ceiling_color_rgb[0],
			all->ceiling_color_rgb[1], all->ceiling_color_rgb[2], 255);
}
