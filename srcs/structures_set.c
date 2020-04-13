/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:56:03 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/12 15:43:09 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	sprite_constructor(t_sprite *sprite, t_img texture, int x, int y)
{
	sprite->texture = texture;
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
}

void	set_sprites(t_window *win)
{
	int j;
	int numSprites = 0;
	int i = 0;
	//COUNT NUMBER OF SPRITES IN MAP
	while (win->set.map[i])
	{
		j = 0;
		while (win->set.map[i][j])
		{
			if (win->set.map[i][j] == '2')
				numSprites++;
			j++;
		}
		i++;
	}
	win->scene.sprite_nb = numSprites;
	//CREATE THE TAB OF SPRITES
	win->scene.sprite_list = malloc(sizeof(t_sprite) * (numSprites));
	i = 0;
	int x = 0;
	while (win->set.map[i])
	{
		j = 0;
		while (win->set.map[i][j])
		{
			if (win->set.map[i][j] == '2')
			{
				sprite_constructor(&win->scene.sprite_list[x], win->set.text_s, i, j);
				x++;
			}
			j++;
		}
		i++;
	}
}

void	set_img_text(t_window *win)
{
	win->set.text_no.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->set.path_no, &win->set.text_no.width, &win->set.text_no.height);
	win->set.text_no.data = (int*)mlx_get_data_addr(win->set.text_no.img_ptr, &win->set.text_no.bpp, &win->set.text_no.s_l, &win->set.text_no.endian);
	
	win->set.text_so.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->set.path_so, &win->set.text_so.width, &win->set.text_so.height);
	win->set.text_so.data = (int*)mlx_get_data_addr(win->set.text_so.img_ptr, &win->set.text_so.bpp, &win->set.text_so.s_l, &win->set.text_so.endian);
	
	win->set.text_ea.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->set.path_ea, &win->set.text_ea.width, &win->set.text_ea.height);
	win->set.text_ea.data = (int*)mlx_get_data_addr(win->set.text_ea.img_ptr, &win->set.text_ea.bpp, &win->set.text_ea.s_l, &win->set.text_ea.endian);
	
	win->set.text_we.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->set.path_we, &win->set.text_we.width, &win->set.text_we.height);
	win->set.text_we.data = (int*)mlx_get_data_addr(win->set.text_we.img_ptr, &win->set.text_we.bpp, &win->set.text_we.s_l, &win->set.text_we.endian);

	win->set.text_s.img_ptr = mlx_xpm_file_to_image(win->mlx_ptr, win->set.path_s, &win->set.text_s.width, &win->set.text_s.height);
	win->set.text_s.data = (int*)mlx_get_data_addr(win->set.text_s.img_ptr, &win->set.text_s.bpp, &win->set.text_s.s_l, &win->set.text_s.endian);
}

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
	set_img_text(win);
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
