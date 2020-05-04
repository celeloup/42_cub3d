/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/04 21:04:59 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"
#include <stdio.h>
#include <time.h>

// int		fading_color(int start_color, int end_color, int time)
// {

// }

void	screen_title(t_window *win)
{
	// choose language (facultatif)
	// animation "a game by"
	// "Celia Leloup"
	// "@celeloup"
	// dialogue poppin
	int color = 0;
	clock_t oldtime = clock();
	
	while (color < 255)
	{
		mlx_string_put(win->mlx_ptr, win->win_ptr, 200, 200, rgb(color, color, color, 1), "this is a test");
		clock_t newtime = clock();
		if (newtime > oldtime + 5000)
		{
			color++;
			oldtime = newtime;
		}
	}
	sleep(2);
}



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
	screen_title(&win);
	mlx_loop_hook(win.mlx_ptr, render_next_frame, &win);
	mlx_hook(win.win_ptr, 2, (1L << 0), key_press, &win);
	mlx_hook(win.win_ptr, 17, (1L << 17), close_window, &win);
	mlx_loop(win.mlx_ptr);
	close_window(&win);
	return (EXIT_SUCCESS);
}

void	dialogue_box(t_window *win, int x, int y)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->ui.dialog_box.img_ptr, x, y);
}

void	animation_text(t_window *win, int frameCount)
{
	static int index = 1;
	static int delay = 0;
	char *text = "This is a dialogue.";
	if (frameCount == 10 && delay < 4)
		delay++;
	if (delay > 3)
	{
		if (index <= (int)ft_strlen(text))
		{
			char *to_print = ft_substr(text, 0, index);
			mlx_string_put(win->mlx_ptr, win->win_ptr, 170, 425, BLACK, to_print);
			free(to_print);
			if (frameCount == 1)
				index += frameCount;
		}
		else
		{
			mlx_string_put(win->mlx_ptr, win->win_ptr, 170, 425, BLACK, text);
			return ;
		}
	}
	
}

int		render_next_frame(t_window *win)
{
	static int test = 0;
	if (test == 0)
		win->frameCount++;
	else
		win->frameCount--;
	if (win->frameCount == 10)
		test = 1;
	else if (win->frameCount == 0)
		test = 0;
	// free(win->img.img_ptr);
	// win->img.img_ptr = mlx_new_image(win->mlx_ptr, win->set.res_x,
	// 	win->set.res_y);
	// win->img.data = (int *)mlx_get_data_addr(win->img.img_ptr,
	// 	&win->img.bpp, &win->img.s_l, &win->img.endian);
	
	
	raycasting(win);
	//minimap(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	if (win->dialogue == 1)
	{
		dialogue_box(win, 150, 400);
		animation_text(win, win->frameCount);
	}
		
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
