/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:11:37 by celeloup          #+#    #+#             */
/*   Updated: 2020/04/20 17:56:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (strisalpha(tab[0]) || strisalpha(tab[1]) || strisalpha(tab[2]))
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

void	set_player(t_window *win, int x, int y)
{
	if (!win->set.player_orientation)
	{
		win->set.player_orientation = win->set.map[x][y];
		win->scene.player.x = x + 0.5;
		win->scene.player.y = y + 0.5;
		if (win->set.player_orientation == 'W')
			win->scene.player_direction = d_vec_constructor(0, -1);
		else if (win->set.player_orientation == 'E')
			win->scene.player_direction = d_vec_constructor(0, 1);
		else if (win->set.player_orientation == 'S')
			win->scene.player_direction = d_vec_constructor(1, 0);
		else if (win->set.player_orientation == 'N')
			win->scene.player_direction = d_vec_constructor(-1, 0);
		win->set.map[x][y] = '0';
	}
	else
		quit_error(win, "Too many players in map. One needed.", NULL, NULL);
}
