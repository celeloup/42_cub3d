/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:25:57 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 17:03:31 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			raycasting(t_window *win)
{
	int			x;
	double		z_buffer[win->set.res_x];
	t_vector_d	ray;
	double		perp_wall_dist;

	x = 0;
	while (x < win->set.res_x)
	{
		ray.x = win->scene.player_direction.x + win->scene.plane.x * \
			(2 * x / (double)win->set.res_x - 1);
		ray.y = win->scene.player_direction.y + win->scene.plane.y * \
			(2 * x / (double)win->set.res_x - 1);
		wall_render(win, x, &perp_wall_dist, ray);
		z_buffer[x] = perp_wall_dist;
		x++;
	}
	sprite_render(win, z_buffer);
	return (1);
}

/*
** pwd is perpendicular wall distance
*/

void		wall_render(t_window *win, int x, double *pwd, t_vector_d ray)
{
	t_vector_i	draw_limits;
	int			color;
	t_vector_i	w_texture;
	double		texture_pos;
	t_img		texture;

	if (shoot_ray(win, win->scene.player, ray, pwd) == 0)
		texture = ray.x < 0 ? win->set.text_no : win->set.text_so;
	else
		texture = ray.y < 0 ? win->set.text_we : win->set.text_ea;
	draw_limits = get_draw_limits(win, (int)(win->set.res_y / *pwd));
	w_texture = get_wall_texture(win, texture, *pwd, ray);
	texture_pos = (draw_limits.x - win->set.res_y / 2 + (int)(win->set.res_y / \
		*pwd) / 2) * (1.0 * texture.height / (int)(win->set.res_y / *pwd));
	v_line(win, x, i_vec_constructor(0, draw_limits.x), win->set.ceil);
	v_line(win, x, i_vec_constructor(draw_limits.y, win->set.res_y), \
		win->set.floor);
	while (draw_limits.x < draw_limits.y)
	{
		w_texture.y = (int)texture_pos & (texture.height - 1);
		texture_pos += 1.0 * texture.height / (int)(win->set.res_y / *pwd);
		color = texture.data[texture.height * w_texture.y + w_texture.x];
		pixel(win, x, draw_limits.x, color);
		draw_limits.x++;
	}
}

t_vector_i	get_draw_limits(t_window *win, int line_height)
{
	t_vector_i	draw_limits;

	draw_limits.x = -line_height / 2 + win->set.res_y / 2;
	if (draw_limits.x < 0)
		draw_limits.x = 0;
	draw_limits.y = line_height / 2 + win->set.res_y / 2;
	if (draw_limits.y >= win->set.res_y)
		draw_limits.y = win->set.res_y;
	return (draw_limits);
}

t_vector_i	get_wall_texture(t_window *win, t_img texture, \
	double perp_wall_dist, t_vector_d ray)
{
	double		wall_x;
	t_vector_i	w_texture;
	int			side;

	if (ft_strcmp(texture.name, "north") == 0 \
		|| ft_strcmp(texture.name, "south") == 0)
		side = 0;
	else
		side = 1;
	if (side == 0)
		wall_x = win->scene.player.y + perp_wall_dist * ray.y;
	else
		wall_x = win->scene.player.x + perp_wall_dist * ray.x;
	wall_x -= floor(wall_x);
	w_texture.x = (int)(wall_x * (double)texture.width);
	if (side == 0 && ray.x > 0)
		w_texture.x = texture.width - w_texture.x - 1;
	if (side == 1 && ray.y < 0)
		w_texture.x = texture.width - w_texture.x - 1;
	return (w_texture);
}
