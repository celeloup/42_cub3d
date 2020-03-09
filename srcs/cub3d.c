/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/09 17:04:27 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <stdio.h>

void	pixel(t_window *win, int x, int y, int color)
{
	if (x >= 0 && x < win->set.res_x && y >= 0 && y < win->set.res_y)
		(win->img.data)[y * win->set.res_x + x] = color;
}

int		rgb(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	init_img(t_img *img)
{
	img->img_ptr = NULL;
	img->data = NULL;
	img->s_l = 0;
	img->bpp = 0;
	img->endian = 0;
}

void	free_img(t_img *img)
{
	(void)img;
	/*
	if (img->img_ptr)
		free(img->img_ptr);
	if (img->data)
		free(img->data);
	*/
}

void	init_settings(t_settings *set)
{
	set->path_ea = NULL;
	set->path_no = NULL;
	set->path_we = NULL;
	set->path_so = NULL;
	set->path_s = NULL;
	set->res_x = 0;
	set->res_y = 0;
	set->floor = 0;
	set->ceil = 0;
	set->map = NULL;
	set->player_orientation = 0;
	set->player_x = -1;
	set->player_y = -1;
}

void	init_win(t_window *win)
{
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->filename = NULL;
	init_settings(&win->set);
	init_img(&win->img);
}

void	free_settings(t_settings *set)
{
	int i;

	if (set->path_ea)
		free(set->path_ea);
	if (set->path_no)
		free(set->path_no);
	if (set->path_we)
		free(set->path_we);
	if (set->path_so)
		free(set->path_so);
	if (set->map)
	{
		i = 0;
		while (set->map[i])
		{
			if (set->map[i])
			{
				free(set->map[i]);
				set->map[i] = NULL;
			}
			i++;
		}
		free(set->map);
		set->map = NULL;
	}
}

void	free_win(t_window *win)
{
	free_settings(&win->set);
	free_img(&win->img);
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

int		try_open_file(char *file)
{
	int ret;

	if ((ret = open(file, O_RDONLY)) == -1)
		return (0);
	close(ret);
	return (1);
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

int		good_elt(char c)
{
	if (c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	check_around(t_window *win, int x, int y, int len)
{
	if (x == 0 || x == len - 1 || !good_elt(win->set.map[x - 1][y])
			|| !good_elt(win->set.map[x][y - 1])
			|| !good_elt(win->set.map[x + 1][y])
			|| !good_elt(win->set.map[x][y + 1])
			|| !good_elt(win->set.map[x + 1][y + 1])
			|| !good_elt(win->set.map[x - 1][y - 1])
			|| !good_elt(win->set.map[x + 1][y - 1])
			|| !good_elt(win->set.map[x - 1][y + 1]))
		quit_error(win, "The map is open.", NULL, NULL);
}

void	set_player(t_window *win, int x, int y)
{
	if (!win->set.player_orientation)
	{
		win->set.player_orientation = win->set.map[x][y];
		win->set.player_x = x;
		win->set.player_y = y;
	}
	else
		quit_error(win, "Too many players in map. One needed.", NULL, NULL);
}

void	check_map(t_window *win)
{
	int x;
	int y;
	int len;

	x = -1;
	len = 0;
	while (win->set.map[len])
		len++;
	while (win->set.map[++x])
	{
		y = 0;
		while (win->set.map[x][y])
		{
			if (!(good_elt(win->set.map[x][y]) || win->set.map[x][y] == ' '))
				quit_error(win, "Bad element in map.", NULL, NULL);
			if (win->set.map[x][y] == '0' || win->set.map[x][y] == 'N'
				|| win->set.map[x][y] == 'S' || win->set.map[x][y] == 'E'
				|| win->set.map[x][y] == 'W' || win->set.map[x][y] == '2')
				check_around(win, x, y, len);
			if (win->set.map[x][y] == 'N' || win->set.map[x][y] == 'S'
				|| win->set.map[x][y] == 'E' || win->set.map[x][y] == 'W')
				set_player(win, x, y);
			y++;
		}
	}
}

void	check_settings(t_window *win)
{
	if (!win->set.res_x || !win->set.res_y || !win->set.path_ea
		|| !win->set.path_no || !win->set.path_s || !win->set.path_so
		|| !win->set.path_we || !win->set.ceil || !win->set.floor
		|| !win->set.map)
		quit_error(win, "Argument missing in cub file.", NULL, NULL);
	check_map(win);
	if (!win->set.player_orientation)
		quit_error(win, "Missing player in map.", NULL, NULL);
}

int		set_settings(int fd, t_window *win)
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
	free(line);
	check_settings(win);
	return (1);
}

int		set_win(t_window *win, char *filename)
{
	int fd;

	if (file_is_ext(filename, ".cub") == 0)
		quit_error(win, CUB_FILE, NULL, NULL);
	if ((fd = open(filename, O_RDONLY)) == -1)
		quit_error(win, OPEN_FILE, NULL, NULL);
	set_settings(fd, win);
	print_settings(win->set);
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr,
		win->set.res_x, win->set.res_y, "Cub3D");
	win->img.img_ptr = mlx_new_image(win->mlx_ptr,
		win->set.res_x, win->set.res_y);
	win->img.data = (int*)mlx_get_data_addr(win->img.img_ptr, &win->img.bpp, \
	&win->img.s_l, &win->img.endian);
	return (1);
}

int		main(int argc, char **argv)
{
	t_window win;

	if (argc < 2 || argc > 3)
	{
		ft_putstr_fd(USAGE, 2);
		return (EXIT_FAILURE);
	}
	init_win(&win);
	if (set_win(&win, argv[1]) == 0)
		return (EXIT_FAILURE);
	//print_map(win.set.map);
	pixel(&win, 100, 100, win.set.ceil);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img.img_ptr, 0, 0);
	hook_event(&win);
	mlx_loop(win.mlx_ptr);
	return (EXIT_SUCCESS);
}
