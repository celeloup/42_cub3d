/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_destructor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:26:54 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/12 11:53:27 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_destructor(t_img *img)
{
	(void)img;
	/*
	if (img->img_ptr)
		free(img->img_ptr);
	if (img->data)
		free(img->data);
	*/
}

void	settings_destructor(t_settings *set)
{
	int i;

	if (set->path_ea)
		free(set->path_ea);
	if (set->path_no)
		free(set->path_no);
	if (set->path_we)
		free(set->path_we);
	if (set->path_so)
		free(set->path_so);
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
	img_destructor(&set->text_ea);
	img_destructor(&set->text_we);
	img_destructor(&set->text_no);
	img_destructor(&set->text_so);
}

void	window_destructor(t_window *win)
{
	settings_destructor(&win->set);
	img_destructor(&win->img);
}
