/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:54:17 by celeloup          #+#    #+#             */
/*   Updated: 2020/04/27 17:29:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

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

void	hook_event(t_window *win)
{
	mlx_hook(win->win_ptr, 2, (1L << 0), key_press, win);
	mlx_hook(win->win_ptr, 17, (1L << 17), close_window, win);
}

int		close_window(t_window *win)
{
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
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
