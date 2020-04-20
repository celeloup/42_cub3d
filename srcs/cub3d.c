/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/04/20 17:48:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

/*
** BONUS LIST IDEA
** - menu de depart
** - minimap
** - editeur map dans minimap
** - pieces secretes
** - mini zelda : tu dois recuperer les trois triforces pour
** acceder à l'epee de legende
** - mini puzzle (trois mecaniques differentes)
** - son musique
** - animation, particule
** - hud
** - petite histoire ?
*/

void	v_line(t_window *win, int x, t_vector_i limits, int color)
{
	while (limits.x < limits.y)
	{
		pixel(win, x, limits.x, color);
		limits.x++;
	}
}

void	draw_square(t_window *win, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel(win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_window *win)
{
	int x;
	int y;
	int offsetx;
	int offsety;

	x = 0;
	offsetx = win->set.res_x - 300;
	while (win->set.map[x])
	{
		y = 0;
		offsety = win->set.res_y - 20;
		while (win->set.map[x][y])
		{
			if (win->set.map[x][y] == '1')
				draw_square(win, y + offsety, x + offsetx, 5, RED);
			if (win->set.map[x][y] == '0')
				draw_square(win, y + offsety, x + offsetx, 5, WHITE);
			if (win->set.map[x][y] == '2')
				draw_square(win, y + offsety, x + offsetx, 5, YELLOW);
			if (win->set.map[x][y] == 'N' || win->set.map[x][y] == 'W')
				draw_square(win, y + offsety, x + offsetx, 5, BLUE);
			if (x == (int)win->scene.player.x && y == (int)win->scene.player.y)
				draw_square(win, y + offsety, x + offsetx, 5, BLUE);
			y++;
			offsety += 5;
		}
		x++;
		offsetx += 5;
	}
}

int		render_next_frame(t_window *win)
{
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, win->set.res_x,
		win->set.res_y);
	win->img.data = (int *)mlx_get_data_addr(win->img.img_ptr,
		&win->img.bpp, &win->img.s_l, &win->img.endian);
	raycasting(win);
	minimap(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	return (1);
}

void	print_sprites(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->sprite_nb)
	{
		printf("sprite %d at (%f,%f)\n",
			i, scene->sprite_list[i].x, scene->sprite_list[i].y);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_window win;

	if (argc < 2 || argc > 3 || (argc == 3 && ft_strcmp(argv[2], "--save")))
	{
		ft_putstr_fd(USAGE, 2);
		return (EXIT_FAILURE);
	}
	window_constructor(&win);
	window_set(&win, argv[1]);
	if (argc == 3)
		screenshot(&win);
	mlx_loop_hook(win.mlx_ptr, render_next_frame, &win);
	hook_event(&win);
	mlx_loop(win.mlx_ptr);
	close_window(&win);
	return (EXIT_SUCCESS);
}
