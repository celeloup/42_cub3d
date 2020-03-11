/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:55:34 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/10 16:27:16 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int		try_open_file(char *file)
{
	int ret;

	if ((ret = open(file, O_RDONLY)) == -1)
		return (0);
	close(ret);
	return (1);
}

int		strisalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
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
	printf("player x = %f\n", set.player_x);
	printf("player y = %f\n", set.player_y);
	printf("player dir %f ; %f\n", set.player_dir_x, set.player_dir_y);
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

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
