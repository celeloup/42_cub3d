/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:25:01 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:25:21 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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