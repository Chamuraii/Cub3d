/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:18:49 by jchamak           #+#    #+#             */
/*   Updated: 2023/10/13 20:59:33 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* GOOD_ANGLES : ensures to always have angles between 0 and 360 */

double	good_angles(t_all *all, double ang)
{
	while (ang >= 360)
		ang -= 360;
	while (ang < 0)
		ang += 360;
	return (ang);
}

/* DIAG_JUMP : prevents the player from jumping between diagonal walls */

int	diag_jump(t_all *all, int x, int y)
{
	x -= (int)all->x;
	y -= (int)all->y;
	if ((x == 1 && y == 1 || x == -1 && y == -1)
		&& all->map[(int)all->y][(int)all->x + x] == 1
		&& all->map[(int)all->y + y][(int)all->x] == 1)
		return (0);
	if ((x == -1 && y == 1 || x == 1 && y == -1)
		&& all->map[(int)all->y][(int)all->x + x] == 1
		&& all->map[(int)all->y - y][(int)all->x] == 1)
		return (0);
	return (1);
}

/* MOVE_PLAYER : changes the position of the player, only if the new position is
not too close to a wall and not a diagonal jump */

void	move_player(t_all *all, double x, double y)
{
	x *= SPEED * 0.1;
	y *= SPEED * 0.1;
	if (all->map[(int)floor(all->y + y)][(int)floor(all->x + x)] != 1
	&& (all->map[(int)floor(all->y + y + 0.05)]
		[(int)floor(all->x + x + 0.05)] != 1)
	&& (all->map[(int)floor(all->y + y - 0.05)]
		[(int)floor(all->x + x - 0.05)] != 1)
		&& diag_jump(all, all->x + x, all->y + y))
	{
		all->x += x;
		all->y += y;
	}
}

/* MY_HOOK : depending on the key pressed, determines the player's new position,
and closes the game if ESC is pressed */

void	my_hook(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		ft_exit(all, 0);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		move_player(all, -cos(all->z * PI / 180),
			sin(all->z * PI / 180));
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		move_player(all, cos(all->z * PI / 180),
			-sin(all->z * PI / 180));
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		move_player(all, cos((all->z - 90) * PI / 180),
			-sin((all->z - 90) * PI / 180));
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		move_player(all, cos((all->z + 90) * PI / 180),
			-sin((all->z + 90) * PI / 180));
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		all->z = good_angles(all, all->z - CAM_SPEED);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		all->z = good_angles(all, all->z + CAM_SPEED);
	mouse(all);
	rays(all);
}
