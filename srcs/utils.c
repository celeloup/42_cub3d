/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:55:34 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/06 12:16:50 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

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
