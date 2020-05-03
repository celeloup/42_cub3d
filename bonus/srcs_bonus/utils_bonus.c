/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:55:34 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:28:28 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"
#include <stdio.h>

t_vector_d	d_vec_constructor(double x, double y)
{
	t_vector_d vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector_i	i_vec_constructor(int x, int y)
{
	t_vector_i vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void		pixel(t_window *win, int x, int y, int color)
{
	if (x >= 0 && x < win->set.res_x && y >= 0 && y < win->set.res_y)
		(win->img.data)[y * win->set.res_x + x] = color;
}

int			rgb(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		v_line(t_window *win, int x, t_vector_i limits, int color)
{
	while (limits.x < limits.y)
	{
		pixel(win, x, limits.x, color);
		limits.x++;
	}
}
