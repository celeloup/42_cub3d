/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 16:38:37 by user42            #+#    #+#             */
/*   Updated: 2020/04/16 20:17:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		sort_sprites(int *order, double *dist, int nb_sprite)
{
	int		sorted;
	int		j;
	double	tmp_dist;
	int		tmp;

	sorted = 1;
	while (sorted)
	{
		sorted = 0;
		j = 0;
		while (j < nb_sprite - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_dist = dist[j + 1];
				dist[j + 1] = dist[j];
				dist[j] = tmp_dist;
				tmp = order[j + 1];
				order[j + 1] = order[j];
				order[j] = tmp;
				sorted = 1;
			}
			j++;
		}
	}
}

/*
** On créé un tableau d'ordre et de distance des sprites et on les remplit
** pour chaque sprites de la map en fonction de leur distance
** par rapport au joueur (pos_x, pos_y).
** Ensuite on tri ces sprites du plus proche au plus éloigné. (sort_sprites)
*/

t_vector_d	get_sprite_transform(t_window *win, int i, int *sprite_order)
{
	t_vector_d	transform;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;

	sprite_x = win->scene.sprite_list[sprite_order[i]].x - win->set.player_x;
	sprite_y = win->scene.sprite_list[sprite_order[i]].y - win->set.player_y;
	inv_det = 1.0 / (win->scene.plane_x * win->set.player_dir_y
		- win->set.player_dir_x * win->scene.plane_y);
	transform.x = inv_det * (win->set.player_dir_y * sprite_x
		- win->set.player_dir_x * sprite_y);
	transform.y = inv_det * (-win->scene.plane_y * sprite_x
		+ win->scene.plane_x * sprite_y);
	free(sprite_order);
	return (transform);
}

t_vector_i	get_sprite_dimension(t_window *win, t_vector_d transform)
{
	t_vector_i sprite;

	if (transform.y != 0)
	{
		sprite.y = abs((int)(win->set.res_y / (transform.y)));
		sprite.x = abs((int)(win->set.res_y / (transform.y)));
	}
	else
	{
		sprite.y = abs((int)win->set.res_y);
		sprite.x = abs((int)win->set.res_y);
	}
	return (sprite);
}

void		sprite_draw(t_window *win, int stripe, t_vector_i sprite,
	int s_screen_x)
{
	int		y;
	int		texture_y;
	int		color;
	int		texture_x;

	texture_x = (int)(256 * (stripe - (-sprite.x / 2 \
		+ s_screen_x)) * win->set.text_s.width / sprite.x) / 256;
	y = ((-sprite.y / 2 + win->set.res_y / 2) < 0 \
		? 0 : -sprite.y / 2 + win->set.res_y / 2);
	while (y < ((sprite.y / 2 + win->set.res_y / 2) >= win->set.res_y \
		? win->set.res_y - 1 : sprite.y / 2 + win->set.res_y / 2))
	{
		texture_y = (((y * 256 - win->set.res_y * 128 + sprite.y * 128) \
			* win->set.text_s.height) / sprite.y) / 256;
		color = win->set.text_s.data[win->set.text_s.width * texture_y \
			+ texture_x];
		if ((color & 0x00FFFFFF) != 0)
			pixel(win, stripe, y, color);
		y++;
	}
}

int			*get_sprite_order(t_window *win)
{
	int		*sprite_order;
	double	sprite_distance[win->scene.sprite_nb];
	int		i;

	sprite_order = (int*)malloc(sizeof(int) * win->scene.sprite_nb);
	i = 0;
	while (i < win->scene.sprite_nb)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((win->set.player_x - win->scene.sprite_list[i].x)
			* (win->set.player_x - win->scene.sprite_list[i].x)
			+ (win->set.player_y - win->scene.sprite_list[i].y)
			* (win->set.player_y - win->scene.sprite_list[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, win->scene.sprite_nb);
	return (sprite_order);
}

int			get_sprite_screen_x(t_window *win, t_vector_d transform)
{
	int		sprite_screen_x;

	if (transform.y != 0)
		sprite_screen_x = (int)((win->set.res_x / 2) \
			* (1 + transform.x / transform.y));
	else
		sprite_screen_x = (int)((win->set.res_x / 2) * (1 + transform.x));
	return (sprite_screen_x);
}

void		sprite_render(t_window *win, double *z_buf)
{
	t_vector_d	transform;
	t_vector_i	sprite;
	int			sprite_screen_x;
	int			stripe;
	int			i;

	i = 0;
	while (i < win->scene.sprite_nb)
	{
		transform = get_sprite_transform(win, i, get_sprite_order(win));
		sprite = get_sprite_dimension(win, transform);
		sprite_screen_x = get_sprite_screen_x(win, transform);
		stripe = (-sprite.x / 2 + sprite_screen_x) < 0 \
			? 0 : -sprite.x / 2 + sprite_screen_x;
		while (stripe < ((sprite.x / 2 + sprite_screen_x) >= win->set.res_x
			? win->set.res_x - 1 : sprite.x / 2 + sprite_screen_x))
		{
			if (transform.y > 0 && stripe > 0 && stripe < win->set.res_x \
				&& transform.y < z_buf[stripe])
				sprite_draw(win, stripe, sprite, sprite_screen_x);
			stripe++;
		}
		i++;
	}
}
