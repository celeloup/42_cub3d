/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:25:57 by user42            #+#    #+#             */
/*   Updated: 2020/04/18 17:23:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vector_d	get_delta_dist(t_vector_d ray)
{
	t_vector_d	delta_dist;

	if (ray.y == 0)
		delta_dist.x = 0;
	else if (ray.x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = fabs(1 / ray.x);
	if (ray.x == 0)
		delta_dist.y = 0;
	else if (ray.y == 0)
		delta_dist.y = 1;
	else
		delta_dist.y = fabs(1 / ray.y);
	return (delta_dist);
}

/*
** Digital Diffencial Analysis
*/

int			dda_algorithm(t_vector_d *side_dist, t_vector_d *delta_dist, \
	t_vector_i step, t_vector_i *map)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map->x += step.x;
		return (0);
	}
	else
	{
		side_dist->y += delta_dist->y;
		map->y += step.y;
		return (1);
	}
}

/*
** shoot_ray returns the side the ray hit.
** Takes the player position, a ray and a pointer to
*/

int			shoot_ray(t_window *win, t_vector_d player, t_vector_d ray, \
	double *perp_wall_dist)
{
	t_vector_d	side_dist;
	t_vector_d	delta_dist;
	t_vector_i	map;
	t_vector_i	step;
	int			side;

	map.x = (int)player.x;
	map.y = (int)player.y;
	delta_dist = get_delta_dist(ray);
	step.x = (ray.x < 0) ? -1 : 1;
	step.y = (ray.y < 0) ? -1 : 1;
	side_dist.x = (ray.x < 0) ? (player.x - map.x) * delta_dist.x \
		: (map.x + 1.0 - player.x) * delta_dist.x;
	side_dist.y = (ray.y < 0) ? (player.y - map.y) * delta_dist.y \
		: (map.y + 1.0 - player.y) * delta_dist.y;
	while (win->set.map[map.x][map.y] != '1')
		side = dda_algorithm(&side_dist, &delta_dist, step, &map);
	if (side == 0)
		*perp_wall_dist = (map.x - player.x + (1 - step.x) / 2) / ray.x;
	else
		*perp_wall_dist = (map.y - player.y + (1 - step.y) / 2) / ray.y;
	return (side);
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
		wall_x = win->set.player_y + perp_wall_dist * ray.y;
	else
		wall_x = win->set.player_x + perp_wall_dist * ray.x;
	wall_x -= floor(wall_x);
	w_texture.x = (int)(wall_x * (double)texture.width);
	if (side == 0 && ray.x > 0)
		w_texture.x = texture.width - w_texture.x - 1;
	if (side == 1 && ray.y < 0)
		w_texture.x = texture.width - w_texture.x - 1;
	return (w_texture);
}

/*
** pwd is perpendicular wall distance
*/

int			test(t_window *win, int x, double *pwd, t_vector_d ray)
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
	draw_line_ver(win, x, 0, draw_limits.x, win->set.ceil);
	draw_line_ver(win, x, draw_limits.y, win->set.res_y, win->set.floor);
	while (draw_limits.x < draw_limits.y)
	{
		w_texture.y = (int)texture_pos & (texture.height - 1);
		texture_pos += 1.0 * texture.height / (int)(win->set.res_y / *pwd);
		color = texture.data[texture.height * w_texture.y + w_texture.x];
		pixel(win, x, draw_limits.x, color);
		draw_limits.x++;
	}
	return (1);
}

int			raycasting(t_window *win)
{
	int			x;
	double		z_buffer[win->set.res_x];
	t_vector_d	ray;
	double		perp_wall_dist;

	x = 0;
	while (x < win->set.res_x)
	{
		ray.x = win->set.player_dir_x + win->scene.plane_x * \
			(2 * x / (double)win->set.res_x - 1);
		ray.y = win->set.player_dir_y + win->scene.plane_y * \
			(2 * x / (double)win->set.res_x - 1);
		test(win, x, &perp_wall_dist, ray);
		z_buffer[x] = perp_wall_dist;
		x++;
	}
	sprite_render(win, z_buffer);
	return (1);
}
