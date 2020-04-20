/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_destructor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:26:54 by celeloup          #+#    #+#             */
/*   Updated: 2020/04/20 20:08:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_destructor(t_img *img)
{
	(void)img;
}

void	scene_destructor(t_scene *scene)
{
	if (scene->sprite_list)
	{
		free(scene->sprite_list);
		scene->sprite_list = NULL;
	}
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
			if (set->map[i])
			{
				free(set->map[i]);
				set->map[i] = NULL;
			}
			i++;
		}
		free(set->map);
		set->map = NULL;
	}
}

void	window_destructor(t_window *win)
{
	settings_destructor(&win->set);
	scene_destructor(&win->scene);
	img_destructor(&win->img);
	if (win->mlx_ptr)
	{
		mlx_destroy_image(win->mlx_ptr, win->set.text_ea.img_ptr);
		mlx_destroy_image(win->mlx_ptr, win->set.text_so.img_ptr);
		mlx_destroy_image(win->mlx_ptr, win->set.text_no.img_ptr);
		mlx_destroy_image(win->mlx_ptr, win->set.text_we.img_ptr);
	}
}
