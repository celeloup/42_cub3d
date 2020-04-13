/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_constructor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:52:47 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/12 11:51:27 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	scene_constructor(t_scene *scene)
{
	scene->plane_x = 0;
	scene->plane_y = 0;
	scene->sprite_list = NULL;
}

void	img_constructor(t_img *img)
{
	img->img_ptr = NULL;
	img->data = NULL;
	img->s_l = 0;
	img->bpp = 0;
	img->endian = 0;
}

void	settings_constructor(t_settings *set)
{
	set->path_ea = NULL;
	set->path_no = NULL;
	set->path_we = NULL;
	set->path_so = NULL;
	set->path_s = NULL;
	img_constructor(&set->text_ea);
	img_constructor(&set->text_we);
	img_constructor(&set->text_no);
	img_constructor(&set->text_so);
	img_constructor(&set->text_s);
	set->res_x = 0;
	set->res_y = 0;
	set->floor = 0;
	set->ceil = 0;
	set->map = NULL;
	set->player_orientation = 0;
	set->player_x = -1;
	set->player_y = -1;
	set->player_dir_x = 0;
	set->player_dir_y = 0;
}

void	window_constructor(t_window *win)
{
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->filename = NULL;
	settings_constructor(&win->set);
	img_constructor(&win->img);
	scene_constructor(&win->scene);
}
