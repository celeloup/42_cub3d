/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:43:08 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:28:41 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	move_forward(t_window *win)
{
	double move_speed;

	move_speed = 0.1;
	if (win->set.map[(int)(win->scene.player.x + win->scene.player_direction.x \
		* move_speed - 0.02)][(int)win->scene.player.y] != '1')
		win->scene.player.x += win->scene.player_direction.x * move_speed;
	if (win->set.map[(int)win->scene.player.x][(int)(win->scene.player.y \
			+ win->scene.player_direction.y * move_speed - 0.02)] != '1')
		win->scene.player.y += win->scene.player_direction.y * move_speed;
}

void	move_backward(t_window *win)
{
	double move_speed;

	move_speed = 0.1;
	if (win->set.map[(int)(win->scene.player.x - win->scene.player_direction.x \
			* move_speed + 0.02)][(int)win->scene.player.y] != '1')
		win->scene.player.x -= win->scene.player_direction.x * move_speed;
	if (win->set.map[(int)win->scene.player.x][(int)(win->scene.player.y \
			- win->scene.player_direction.y * move_speed + 0.02)] != '1')
		win->scene.player.y -= win->scene.player_direction.y * move_speed;
}

void	move_right(t_window *win)
{
	double move_speed;

	move_speed = 0.1;
	if (win->set.map[(int)(win->scene.player.x + win->scene.plane.x \
			* move_speed - 0.02)][(int)win->scene.player.y] != '1')
		win->scene.player.x += win->scene.plane.x * move_speed;
	if (win->set.map[(int)win->scene.player.x][(int)(win->scene.player.y \
			+ win->scene.plane.y * move_speed - 0.02)] != '1')
		win->scene.player.y += win->scene.plane.y * move_speed;
}

void	move_left(t_window *win)
{
	double move_speed;

	move_speed = 0.1;
	if (win->set.map[(int)(win->scene.player.x - win->scene.plane.x \
		* move_speed + 0.02)][(int)win->scene.player.y] != '1')
		win->scene.player.x -= win->scene.plane.x * move_speed;
	if (win->set.map[(int)win->scene.player.x][(int)(win->scene.player.y \
		- win->scene.plane.y * move_speed + 0.02)] != '1')
		win->scene.player.y -= win->scene.plane.y * move_speed;
}
