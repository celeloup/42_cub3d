/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:56:03 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/10 17:27:48 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	window_set(t_window *win, char *filename)
{
	int fd;

	if (file_is_ext(filename, ".cub") == 0)
		quit_error(win, CUB_FILE, NULL, NULL);
	if ((fd = open(filename, O_RDONLY)) == -1)
		quit_error(win, OPEN_FILE, NULL, NULL);
	settings_set(fd, win);
	//print_settings(win->set);
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr,
		win->set.res_x, win->set.res_y, "Cub3D");
	win->img.img_ptr = mlx_new_image(win->mlx_ptr,
		win->set.res_x, win->set.res_y);
	win->img.data = (int*)mlx_get_data_addr(win->img.img_ptr, &win->img.bpp, \
	&win->img.s_l, &win->img.endian);
}

void	settings_set(int fd, t_window *win)
{
	char		*line;
	int			ret;

	while ((ret = get_next_line(fd, &line)))
	{
		if (!parse_arguments(win, line))
		{
			if (good_elt(line[0]) || line[0] == ' ')
				add_to_map(win, line);
			else if (line && win->set.map != NULL)
			{
				free(line);
				quit_error(win, "Bad formating of cub file.", NULL, NULL);
			}
			else if (line[0])
			{
				free(line);
				quit_error(win, INVALID_DES, NULL, NULL);
			}
		}
		free(line);
	}
	check_settings(win);
}

int		parse_arguments(t_window *win, char *line)
{
	if (win->set.map != NULL)
		return (0);
	if (line[0] == 'R' && line[1] == ' ')
		set_res(win, line);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		set_texture(win, line);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		set_texture(win, line);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		set_texture(win, line);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		set_texture(win, line);
	else if (line[0] == 'S' && line[1] == ' ')
		set_texture(win, line);
	else if (line[0] == 'F' && line[1] == ' ')
		set_color(win, line + 2, 'F');
	else if (line[0] == 'C' && line[1] == ' ')
		set_color(win, line + 2, 'C');
	else
		return (0);
	return (1);
}

void	add_to_map(t_window *win, char *line)
{
	int		len;
	char	**tmp;

	if (!win->set.map)
	{
		win->set.map = (char**)malloc(sizeof(char*) * 1);
		if (!win->set.map)
			quit_error(win, "ERROR MALLOC", NULL, NULL);
		win->set.map[0] = 0;
	}
	len = 0;
	while (win->set.map[len])
		len++;
	tmp = malloc(sizeof(char *) * (len + 2));
	len = 0;
	while (win->set.map[len])
	{
		tmp[len] = ft_strdup(win->set.map[len]);
		len++;
	}
	tmp[len] = ft_strdup(line);
	tmp[len + 1] = 0;
	free_tab(win->set.map);
	win->set.map = tmp;
}
