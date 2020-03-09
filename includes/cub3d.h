/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:59 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/09 15:02:49 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define LEAKS 0

# include "../libft/src/libft.h"
# include "error_define.h"
# include "lgl_define.h"
# include <mlx.h>
# include <fcntl.h>

# define WHITE 0xFFFFFF
# define RED 0xD62727
# define YELLOW 0xEAD725
# define GREEN 0x03BF23
# define BLUE 0x3A7ECC
# define PURPLE 0x925CC3
# define BLACK 0x000000

/*
typedef	struct			s_sprite
{
	void				*img;
	int					width;
	int					height;
}						t_sprite;
*/

typedef struct			s_settings
{
	char				*path_no;
	char				*path_so;
	char				*path_we;
	char				*path_ea;
	char				*path_s;
	int					res_x;
	int					res_y;
	int					floor;
	int					ceil;
	char				**map;
	char				player_orientation;
	int					player_x;
	int					player_y;
	//void				*t_north;
	//void				*t_south;
	//void				*t_west;
	//void				*t_east;
	//void				*t_s;
}						t_settings;

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					s_l;
	int					bpp;
	int					endian;
	char				pad[4];
}						t_img;

typedef struct			s_window
{
	t_settings			set;
	char				*filename;
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
}						t_window;

/*
** PARSING.C
*/
int		file_is_ext(char *file, char *ext);
void	set_res(t_window *win, char *line);
void	set_color(t_window *win, char *line, char c);
void	set_texture(t_window *win, char *line);
int		quit_error(t_window *win, char *error, void *tofree, void (*f)(char**));

/*
** EVENTS.C
*/
int		key_press(int keycode, t_window *win);
void	hook_event(t_window *win);
int		close_window(t_window *win);

/*
** CUB3D.c
*/
void	pixel(t_window *win, int x, int y, int color);
int		rgb(int r, int g, int b, int t);
void	init_win(t_window *win);
void	free_win(t_window *win);
void	add_to_map(t_window *win, char *line);
int		try_open_file(char *file);
int		set_settings(int fd, t_window *win);
int		set_win(t_window *win, char *filename);

/*
** UTILS.C
*/
int		strisalpha(char *str);
void	print_settings(t_settings set);
void	free_tab(char **tab);
int		len_tab(char **tab);

#endif
