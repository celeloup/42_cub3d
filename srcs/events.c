/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:54:17 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 17:12:34 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_press(int keycode, t_window *win)
{
	if (keycode == K_ESC)
		close_window(win);
	if (keycode == K_Z)
		move_forward(win);
	if (keycode == K_Q)
		move_left(win);
	if (keycode == K_S)
		move_backward(win);
	if (keycode == K_D)
		move_right(win);
	if (keycode == K_AR_R)
		look_right(win);
	if (keycode == K_AR_L)
		look_left(win);
	return (0);
}

int		close_window(t_window *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	window_destructor(win);
	if (LEAKS)
		system("valgrind --tool=memcheck --leak-check=summary \
			--leak-resolution=high --show-reachable=yes ./Cub3D");
	exit(0);
	return (0);
}

int		quit_error(t_window *win, char *error, void *tofree, void (*f)(char**))
{
	window_destructor(win);
	ft_putstr_fd("\033[0;31mError: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n\033[0m", 2);
	if (tofree && f)
		(*f)(tofree);
	if (LEAKS)
		system("leaks Cub3D");
	exit(0);
	return (0);
}

void	look_right(t_window *win)
{
	double rot_speed;
	double old_dir_x;
	double old_plane_x;

	rot_speed = 0.04;
	old_dir_x = win->scene.player_direction.x;
	win->scene.player_direction.x = win->scene.player_direction.x \
		* cos(-rot_speed) - win->scene.player_direction.y * sin(-rot_speed);
	win->scene.player_direction.y = old_dir_x * sin(-rot_speed) \
		+ win->scene.player_direction.y * cos(-rot_speed);
	old_plane_x = win->scene.plane.x;
	win->scene.plane.x = win->scene.plane.x * cos(-rot_speed) \
		- win->scene.plane.y * sin(-rot_speed);
	win->scene.plane.y = old_plane_x * sin(-rot_speed) \
		+ win->scene.plane.y * cos(-rot_speed);
}

void	look_left(t_window *win)
{
	double rot_speed;
	double old_dir_x;
	double old_plane_x;

	rot_speed = -0.04;
	old_dir_x = win->scene.player_direction.x;
	win->scene.player_direction.x = win->scene.player_direction.x \
		* cos(-rot_speed) - win->scene.player_direction.y * sin(-rot_speed);
	win->scene.player_direction.y = old_dir_x * sin(-rot_speed) \
		+ win->scene.player_direction.y * cos(-rot_speed);
	old_plane_x = win->scene.plane.x;
	win->scene.plane.x = win->scene.plane.x * cos(-rot_speed) \
		- win->scene.plane.y * sin(-rot_speed);
	win->scene.plane.y = old_plane_x * sin(-rot_speed) + win->scene.plane.y \
		* cos(-rot_speed);
}
