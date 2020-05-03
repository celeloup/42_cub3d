/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:02:21 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:28:39 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"
#include <math.h>
#include <stdio.h>

int		file_is_ext(char *file, char *ext)
{
	int len;
	int len_ext;

	len = ft_strlen(file);
	len_ext = ft_strlen(ext);
	while (len_ext > 0)
	{
		if (file[len] != ext[len_ext])
			return (0);
		len--;
		len_ext--;
	}
	return (1);
}

int		good_elt(char c)
{
	if (c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	check_around(t_window *win, int x, int y, int len)
{
	if (x == 0 || x == len - 1 || !good_elt(win->set.map[x - 1][y])
			|| !good_elt(win->set.map[x][y - 1])
			|| !good_elt(win->set.map[x + 1][y])
			|| !good_elt(win->set.map[x][y + 1])
			|| !good_elt(win->set.map[x + 1][y + 1])
			|| !good_elt(win->set.map[x - 1][y - 1])
			|| !good_elt(win->set.map[x + 1][y - 1])
			|| !good_elt(win->set.map[x - 1][y + 1]))
		quit_error(win, "The map is open.", NULL, NULL);
}

void	check_map(t_window *win)
{
	int x;
	int y;
	int len;

	x = -1;
	len = 0;
	while (win->set.map[len])
		len++;
	while (win->set.map[++x])
	{
		y = 0;
		while (win->set.map[x][y])
		{
			if (!(good_elt(win->set.map[x][y]) || win->set.map[x][y] == ' '))
				quit_error(win, "Bad element in map.", NULL, NULL);
			if (win->set.map[x][y] == '0' || win->set.map[x][y] == 'N'
				|| win->set.map[x][y] == 'S' || win->set.map[x][y] == 'E'
				|| win->set.map[x][y] == 'W' || win->set.map[x][y] == '2')
				check_around(win, x, y, len);
			if (win->set.map[x][y] == 'N' || win->set.map[x][y] == 'S'
				|| win->set.map[x][y] == 'E' || win->set.map[x][y] == 'W')
				set_player(win, x, y);
			y++;
		}
	}
}

void	check_settings(t_window *win)
{
	if (win->set.res_x == -1 || win->set.res_y == -1 || !win->set.path_ea
		|| !win->set.path_no || !win->set.path_s || !win->set.path_so
		|| !win->set.path_we || win->set.ceil == -1 || win->set.floor == -1
		|| !win->set.map)
		quit_error(win, "Argument missing in cub file.", NULL, NULL);
	check_map(win);
	if (!win->set.player_orientation)
		quit_error(win, "Missing player in map.", NULL, NULL);
}
