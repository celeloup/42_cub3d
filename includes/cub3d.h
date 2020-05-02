/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:59 by celeloup          #+#    #+#             */
/*   Updated: 2020/05/02 17:21:38 by celeloup         ###   ########.fr       */
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

typedef struct	s_vector_d
{
	double		x;
	double		y;
}				t_vector_d;

typedef struct	s_vector_i
{
	int			x;
	int			y;
}				t_vector_i;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			s_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
	char		pad[4];
	char		*name;
}				t_img;

typedef	struct	s_sprite
{
	t_img		texture;
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_settings
{
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*path_s;
	t_img		text_no;
	t_img		text_so;
	t_img		text_we;
	t_img		text_ea;
	t_img		text_s;
	int			res_x;
	int			res_y;
	int			floor;
	int			ceil;
	char		**map;
	char		player_orientation;
	char		pad[7];
}				t_settings;

typedef struct	s_scene
{
	t_vector_d	plane;
	t_vector_d	player;
	t_vector_d	player_direction;
	t_sprite	*sprite_list;
	int			sprite_nb;
	char		pad[4];
}				t_scene;

typedef struct	s_window
{
	char		*filename;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_settings	set;
	t_scene		scene;
}				t_window;

/*
** CUB3D.C
*/
int				render_next_frame(t_window *win);
void			get_file_header(unsigned char *file_header, t_window *win,
	int pad_size);
void			screenshot(t_window *win);
int				try_open_file(char *file);

/*
** STRUCTURES_CONSTRUCTOR.C
*/
void			window_constructor(t_window *win);
void			settings_constructor(t_settings *set);
void			img_constructor(t_img *img);
void			scene_constructor(t_scene *scene);

/*
**	STRUCTURES_DESTRUCTOR.C
*/
void			window_destructor(t_window *win);
void			settings_destructor(t_settings *set);
void			scene_destructor(t_scene *scene);
void			img_destructor(t_img *img);

/*
** STRUCTURES_SET.C
*/
void			window_set(t_window *win, char *filename);
void			settings_set(int fd, t_window *win);
int				parse_arguments(t_window *win, char *line);
void			scene_set(t_window *win);
void			set_img_texture(t_window *win);

/*
** SETTINGS_SET.C
*/
void			set_res(t_window *win, char *line);
void			set_color(t_window *win, char *line, char c);
void			set_texture(t_window *win, char *line);
void			set_player(t_window *win, int x, int y);
void			add_to_map(t_window *win, char *line);

/*
** PARSING.C
*/
int				file_is_ext(char *file, char *ext);
int				good_elt(char c);
void			check_around(t_window *win, int x, int y, int len);
void			check_map(t_window *win);
void			check_settings(t_window *win);

/*
** RAYCASTING.C
*/
int				raycasting(t_window *win);
void			wall_render(t_window *win, int x, double *pwd, t_vector_d ray);
t_vector_i		get_draw_limits(t_window *win, int line_height);
t_vector_i		get_wall_texture(t_window *win, t_img texture, \
			double perp_wall_dist, t_vector_d ray);

/*
** RAY_SHOOTING.C
*/
int				shoot_ray(t_window *win, t_vector_d player, t_vector_d ray, \
			double *perp_wall_dist);
t_vector_d		get_delta_dist(t_vector_d ray);
int				dda_algorithm(t_vector_d *side_dist, t_vector_d *delta_dist, \
			t_vector_i step, t_vector_i *map);

/*
** SPRITE_SET.C
*/
void			sprite_constructor(t_sprite *sprite, t_img texture, int x, \
			int y);
void			set_sprites(t_window *win);
int				count_sprites(char **map);
int				*get_sprite_order(t_window *win);
void			sort_sprites(int *order, double *dist, int nb_sprite);

/*
** SPRITE_RENDER.C
*/
void			sprite_render(t_window *win, double *z_buf);
t_vector_d		get_sprite_transform(t_window *win, int i, int *sprite_order);
t_vector_i		get_sprite_dimension(t_window *win, t_vector_d transform);
int				get_sprite_screen_x(t_window *win, t_vector_d transform);
void			sprite_draw(t_window *win, int stripe, t_vector_i sprite,
	int s_screen_x);

/*
** EVENTS.C
*/
int				key_press(int keycode, t_window *win);
int				close_window(t_window *win);
int				quit_error(t_window *win, char *error, void *tofree,
	void (*f)(char**));
void			look_right(t_window *win);
void			look_left(t_window *win);

/*
** MOVE.C
*/
void			move_forward(t_window *win);
void			move_backward(t_window *win);
void			move_right(t_window *win);
void			move_left(t_window *win);

/*
** UTILS.C
*/
t_vector_d		d_vec_constructor(double x, double y);
t_vector_i		i_vec_constructor(int x, int y);
void			pixel(t_window *win, int x, int y, int color);
int				rgb(int r, int g, int b, int t);
void			v_line(t_window *win, int x, t_vector_i limits, \
	int color);

#endif
