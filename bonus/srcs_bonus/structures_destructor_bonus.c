/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_destructor_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:26:54 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:28:24 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	window_destructor(t_window *win)
{
	settings_destructor(&win->set);
	scene_destructor(&win->scene);
	if (win->mlx_ptr)
	{
		free(win->set.text_no.img_ptr);
		free(win->set.text_so.img_ptr);
		free(win->set.text_ea.img_ptr);
		free(win->set.text_we.img_ptr);
		free(win->set.text_s.img_ptr);
	}
	free(win->mlx_ptr);
	free(win->img.img_ptr);
}

void	settings_destructor(t_settings *set)
{
	int i;

	if (set->path_ea != NULL)
		free(set->path_ea);
	if (set->path_no)
		free(set->path_no);
	if (set->path_we)
		free(set->path_we);
	if (set->path_so)
		free(set->path_so);
	if (set->path_s)
		free(set->path_s);
	if (set->map)
	{
		i = 0;
		while (set->map[i])
		{
			free(set->map[i]);
			set->map[i] = NULL;
			i++;
		}
		free(set->map);
		set->map = NULL;
	}
}

void	scene_destructor(t_scene *scene)
{
	if (scene->sprite_list)
	{
		free(scene->sprite_list);
		scene->sprite_list = NULL;
	}
}

void	img_destructor(t_img *img)
{
	free(img->img_ptr);
}
