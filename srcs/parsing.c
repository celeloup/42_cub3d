/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:02:21 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/09 14:06:17 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

int		quit_error(t_window *win, char *error, void *tofree, void (*f)(char**))
{
	free_win(win);
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

void	set_res(t_window *win, char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (len_tab(tab) != 3)
		quit_error(win, NB_RES, tab, free_tab);
	if (strisalpha(tab[1]) || strisalpha(tab[2]))
		quit_error(win, ARG_RES, tab, free_tab);
	win->set.res_x = ft_atoi(tab[1]);
	win->set.res_y = ft_atoi(tab[2]);
	free_tab(tab);
	if (win->set.res_x < 50 || win->set.res_y < 50)
		quit_error(win, VAL_RES, NULL, NULL);
	win->set.res_x = fmin(win->set.res_x, SCREEN_MAX_X);
	win->set.res_y = fmin(win->set.res_y, SCREEN_MAX_Y);
}

void	set_color(t_window *win, char *line, char c)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (len_tab(tab) != 1)
		quit_error(win, NB_COLOR, tab, free_tab);
	free_tab(tab);
	tab = ft_split(line, ',');
	if (len_tab(tab) != 3)
		quit_error(win, NB_COLOR, tab, free_tab);
	if (strisalpha(tab[0]) || strisalpha(tab[0]) || strisalpha(tab[2]))
		quit_error(win, ARG_COLOR, tab, free_tab);
	if (ft_atoi(tab[0]) < 0 || ft_atoi(tab[0]) > 255 || ft_atoi(tab[1]) < 0
		|| ft_atoi(tab[1]) > 255 || ft_atoi(tab[2]) < 0
		|| ft_atoi(tab[2]) > 255)
		quit_error(win, VAL_COLOR, NULL, NULL);
	if (c == 'C')
		win->set.ceil = rgb(ft_atoi(tab[0]), ft_atoi(tab[1]),
			ft_atoi(tab[2]), 0);
	else
		win->set.floor = rgb(ft_atoi(tab[0]), ft_atoi(tab[1]),
			ft_atoi(tab[2]), 0);
	free_tab(tab);
}

void	set_texture(t_window *win, char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (len_tab(tab) != 2)
		quit_error(win, NB_TEX, tab, free_tab);
	if (!file_is_ext(tab[1], ".xpm"))
		quit_error(win, XPM_FILE, tab, free_tab);
	if ((try_open_file(tab[1])) == 0)
		quit_error(win, OPEN_TEX_FILE, tab, free_tab);
	if (tab[0][0] == 'N')
		win->set.path_no = ft_strdup(tab[1]);
	else if (tab[0][0] == 'S' && tab[0][1] == 'O')
		win->set.path_so = ft_strdup(tab[1]);
	else if (tab[0][0] == 'W')
		win->set.path_we = ft_strdup(tab[1]);
	else if (tab[0][0] == 'E')
		win->set.path_ea = ft_strdup(tab[1]);
	else if (tab[0][0] == 'S' && tab[0][1] == '\0')
		win->set.path_s = ft_strdup(tab[1]);
	free_tab(tab);
}
