/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:59 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/10 16:26:11 by celeloup         ###   ########.fr       */
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
# include <math.h>

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
	double				player_x;
	double				player_y;
	double				player_dir_x;
	double				player_dir_y;
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

typedef struct			s_scene
{
	double 				plane_x;
	double				plane_y;
}						t_scene;

typedef struct			s_window
{
	t_settings			set;
	char				*filename;
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_scene				scene;
}						t_window;

/*
** STRUCTURES_CONSTRUCTOR.C
*/
void	img_constructor(t_img *img);
void	settings_constructor(t_settings *set);
void	window_constructor(t_window *win);

/*
**	STRUCTURES_DESTRUCTOR.C
*/
void	img_destructor(t_img *img);
void	settings_destructor(t_settings *set);
void	window_destructor(t_window *win);

/*
** STRUCTURES_SET.C
*/
void	window_set(t_window *win, char *filename);
void	settings_set(int fd, t_window *win);
int		parse_arguments(t_window *win, char *line);
void	add_to_map(t_window *win, char *line);

/*
** SETTINGS_SET.C
*/
void	set_res(t_window *win, char *line);
void	set_color(t_window *win, char *line, char c);
void	set_texture(t_window *win, char *line);
void	set_player(t_window *win, int x, int y);

/*
** PARSING.C
*/
int		file_is_ext(char *file, char *ext);
int		good_elt(char c);
void	check_around(t_window *win, int x, int y, int len);
void	check_map(t_window *win);
void	check_settings(t_window *win);

/*
** EVENTS.C
*/
int		key_press(int keycode, t_window *win);
void	hook_event(t_window *win);
int		close_window(t_window *win);
int		quit_error(t_window *win, char *error, void *tofree, void (*f)(char**));

/*
** CUB3D.c
*/
void	pixel(t_window *win, int x, int y, int color);
int		rgb(int r, int g, int b, int t);


/*
** UTILS.C
*/
int		try_open_file(char *file);
int		strisalpha(char *str);
void	print_map(char **map);
void	print_settings(t_settings set);
void	free_tab(char **tab);
int		len_tab(char **tab);

#endif
