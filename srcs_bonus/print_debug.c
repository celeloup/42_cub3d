/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:31:45 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 14:32:23 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_sprites(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->sprite_nb)
	{
		printf("sprite %d at (%f,%f)\n",
			i, scene->sprite_list[i].x, scene->sprite_list[i].y);
		i++;
	}
}

void	print_settings(t_settings set)
{
	printf("\n  MAP VARIABLES  \n");
	printf("\nRes X -> %d\nRes Y -> %d\n", set.res_x, set.res_y);
	printf("path_no -> %s\n", set.path_no);
	printf("path_so -> %s\n", set.path_so);
	printf("path_we -> %s\n", set.path_we);
	printf("path_ea -> %s\n", set.path_ea);
	printf("path_s -> %s\n", set.path_s);
	printf("floor -> %x\n", set.floor);
	printf("ceil -> %x\n\n", set.ceil);
	print_map(set.map);
}

void	print_map(char **map)
{
	int i;

	printf("MAP\n");
	i = 0;
	while (map[i])
	{
		ft_putstr(map[i]);
		ft_putchar('\n');
		i++;
	}
}
