/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:59 by celeloup          #+#    #+#             */
/*   Updated: 2020/04/17 16:23:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define LEAKS 0

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

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

typedef struct			s_vector_d
{
	double				x;
	double				y;
}						t_vector_d;

typedef struct			s_vector_i
{
	int					x;
	int					y;
}						t_vector_i;

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					s_l;
	int					bpp;
	int					endian;
	int					width;
	int					height;
	char				*name;
	char				pad[4];
}						t_img;

typedef	struct			s_sprite
{
	t_img				texture;
	double				x;
	double				y;
}						t_sprite;


typedef struct			s_settings
{
	char				*path_no;
	char				*path_so;
	char				*path_we;
	char				*path_ea;
	char				*path_s;
	t_img				text_no;
	t_img				text_so;
	t_img				text_we;
	t_img				text_ea;
	t_img				text_s;
	int					res_x;
	int					res_y;
	int					floor;
	int					ceil;
	char				**map;
	char				player_orientation;
	char				pad[7];
	double				player_x;
	double				player_y;
	double				player_dir_x;
	double				player_dir_y;
}						t_settings;


typedef struct			s_scene
{
	double 				plane_x;
	double				plane_y;
	//wall (tab)
	t_sprite			*sprite_list;
	int					sprite_nb;
	//player x y
	//player dir x y
	//map ?
	char				pad[4];
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
void	set_sprites(t_window *win);

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
void	sort_sprites(int *order, double *dist, int nb_sprite);
int		render_next_frame(t_window *win);
int		raycasting(t_window *win, t_vector_d player);
void	draw_line_ver(t_window *win, int x, int start, int end, int color);

/*
** UTILS.C
*/
int		try_open_file(char *file);
int		strisalpha(char *str);
void	print_map(char **map);
void	print_settings(t_settings set);
void	free_tab(char **tab);
int		len_tab(char **tab);

/*
** SPRITE.C
*/
void		sort_sprites(int *order, double *dist, int nb_sprite);
t_vector_d	get_sprite_transform(t_window *win, int i, int *sprite_order);
t_vector_i	get_sprite_dimension(t_window *win, t_vector_d transform);
void		sprite_draw(t_window *win, int stripe, t_vector_i sprite,
	int s_screen_x);
int			*get_sprite_order(t_window *win);
int			get_sprite_screen_x(t_window *win, t_vector_d transform);
void		sprite_render(t_window *win, double *z_buf);

/*
** NORME.C (fonctions normées à distribuer dans fichiers)
*/
void	get_file_header(unsigned char *file_header, t_window *win, int pad_size);
void	screenshot(t_window *win);

#endif
