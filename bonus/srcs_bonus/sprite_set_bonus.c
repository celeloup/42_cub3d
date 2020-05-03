/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_set_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:55:52 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/03 12:28:11 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	sprite_constructor(t_sprite *sprite, t_img texture, int x, int y)
{
	sprite->texture = texture;
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
}

void	set_sprites(t_window *win)
{
	int j;
	int i;
	int x;

	win->scene.sprite_nb = count_sprites(win->set.map);
	if (!(win->scene.sprite_list = malloc(sizeof(t_sprite) \
		* (win->scene.sprite_nb))))
		quit_error(win, "Couldn't allocate memory (malloc).", NULL, NULL);
	i = 0;
	x = 0;
	while (win->set.map[i])
	{
		j = 0;
		while (win->set.map[i][j])
		{
			if (win->set.map[i][j] == '2')
			{
				sprite_constructor(&win->scene.sprite_list[x], \
					win->set.text_s, i, j);
				x++;
			}
			j++;
		}
		i++;
	}
}

int		count_sprites(char **map)
{
	int i;
	int j;
	int sprites_nb;

	i = 0;
	sprites_nb = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				sprites_nb++;
			j++;
		}
		i++;
	}
	return (sprites_nb);
}

int		*get_sprite_order(t_window *win)
{
	int		*sprite_order;
	double	sprite_distance[win->scene.sprite_nb];
	int		i;

	if (!(sprite_order = (int*)malloc(sizeof(int) * win->scene.sprite_nb)))
	{
		ft_putstr_fd("\033[0;31mError: ", 2);
		ft_putstr_fd("Couldn't allocate memory (malloc).", 2);
		ft_putstr_fd("\n\033[0m", 2);
		close_window(win);
	}
	i = 0;
	while (i < win->scene.sprite_nb)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((win->scene.player.x \
			- win->scene.sprite_list[i].x) \
			* (win->scene.player.x - win->scene.sprite_list[i].x) \
			+ (win->scene.player.y - win->scene.sprite_list[i].y) \
			* (win->scene.player.y - win->scene.sprite_list[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, win->scene.sprite_nb);
	return (sprite_order);
}

void	sort_sprites(int *order, double *dist, int nb_sprite)
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
