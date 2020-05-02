/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 17:19:32 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		main(int argc, char **argv)
{
	t_window win;

	if (argc < 2 || argc > 3 || (argc == 3 && ft_strcmp(argv[2], "--save")))
	{
		ft_putstr_fd(USAGE, 2);
		return (EXIT_FAILURE);
	}
	window_constructor(&win);
	window_set(&win, argv[1]);
	if (argc == 3)
		screenshot(&win);
	mlx_loop_hook(win.mlx_ptr, render_next_frame, &win);
	mlx_hook(win.win_ptr, 2, (1L << 0), key_press, &win);
	mlx_hook(win.win_ptr, 17, (1L << 17), close_window, &win);
	mlx_loop(win.mlx_ptr);
	close_window(&win);
	return (EXIT_SUCCESS);
}

int		render_next_frame(t_window *win)
{
	free(win->img.img_ptr);
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, win->set.res_x,
		win->set.res_y);
	win->img.data = (int *)mlx_get_data_addr(win->img.img_ptr,
		&win->img.bpp, &win->img.s_l, &win->img.endian);
	raycasting(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	return (1);
}

/*
** https://stackoverflow.com/questions/2654480
** /writing-bmp-image-in-pure-c-c-without-other-libraries
*/

void	screenshot(t_window *win)
{
	int				fd;
	unsigned char	padding[3];
	unsigned char	file_header[14 + 40];
	int				i;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0700);
	padding[0] = 0;
	padding[1] = 0;
	padding[2] = 0;
	ft_bzero(file_header, 14 + 40);
	get_file_header(file_header, win, (4 - (win->set.res_x * 4) % 4) % 4);
	render_next_frame(win);
	write(fd, file_header, 14 + 40);
	i = win->set.res_y - 1;
	while (i > 0)
	{
		write(fd, (unsigned char *)win->img.data + (i * win->set.res_x * 4),
			4 * win->set.res_x);
		write(fd, padding, (4 - (win->set.res_x * 4) % 4) % 4);
		i--;
	}
	close(fd);
	ft_putstr_fd("\033[32;1mScreenshot saved as 'screenshot.bmp'.\033[0m\n", 1);
	close_window(win);
}

void	get_file_header(unsigned char *file_header, t_window *win, int pad_size)
{
	int	file_size;

	file_size = 14 + 40 + (4 * win->set.res_x + pad_size) * win->set.res_y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	file_header[0 + 14] = (unsigned char)(40);
	file_header[4 + 14] = (unsigned char)(win->set.res_x);
	file_header[5 + 14] = (unsigned char)(win->set.res_x >> 8);
	file_header[6 + 14] = (unsigned char)(win->set.res_x >> 16);
	file_header[7 + 14] = (unsigned char)(win->set.res_x >> 24);
	file_header[8 + 14] = (unsigned char)(win->set.res_y);
	file_header[9 + 14] = (unsigned char)(win->set.res_y >> 8);
	file_header[10 + 14] = (unsigned char)(win->set.res_y >> 16);
	file_header[11 + 14] = (unsigned char)(win->set.res_y >> 24);
	file_header[12 + 14] = (unsigned char)(1);
	file_header[14 + 14] = (unsigned char)(4 * 8);
}

int		try_open_file(char *file)
{
	int ret;

	if ((ret = open(file, O_RDONLY)) == -1)
		return (0);
	close(ret);
	return (1);
}
