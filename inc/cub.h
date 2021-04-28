/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:51:44 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 19:30:33 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# ifdef	MAC_SYSTEM
#  include "../minilibx-Darwin/mlx.h"
# elif	LINUX_SYSTEM
#  include "../minilibx-Linux/mlx.h"
# endif
# ifdef	MAC_SYSTEM
#  include "keycode_mac.h"
# elif	LINUX_SYSTEM
#  include "keycode_linux.h"
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "libft.h"
# define SPACE				' '
# define EMPTY				'0'
# define WALL				'1'
# define OBJECT				'2'
# define NORTH				'N'
# define SOUTH				'S'
# define WEST				'W'
# define EAST				'E'
# define NO					1
# define SO					0
# define EA					3
# define WE					2
# define MAX_TEXTURES		4
# define MAX_LEN			10
# define TOTAL_IDS			8
# define TOTAL_INFO			9
# define VIEW_ANGLE			32.5
# define SQUARES_SEC		0.09
# define RADIANS_SEC		0.03
# define AND_ING			8355711
# define FRAME_TIME			1000.0
# define BYTE				256
# define BMP_HEADER_BYTES	54
# define DATA_INIT			54
# define BMP_HEADER_SIZE	40
# define NUM_PLANES			1
# define HORIZ_RESOLUTION	24

typedef struct s_render {
	int			x;
	int			y;
}				t_render;

typedef struct s_textures {
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*path_sp;
}				t_textures;

typedef struct s_colors {
	int			rgb_s[3];
	int			rgb_f[3];
}				t_colors;

typedef struct s_minilibx {
	void		*mlx;
	void		*window;
}				t_minilix;

typedef struct s_img {
	void		*img;
	int			*addr;
	int			hei;
	int			wid;
	int			sz;
	int			endian;
	int			bpp;
}				t_img;

typedef struct s_sprite {
	void		*img;
	int			*addr;
	int			hei;
	int			wid;
	int			sz;
	int			endian;
	int			bpp;
	double		posx;
	double		posy;
	int			draw_starty;
	int			draw_startx;
	int			draw_endy;
	int			draw_endx;
	int			h;
	int			w;
	int			screenx;
	double		*zbuf;
	int			color;
}				t_sprite;

typedef struct s_sprites {
	double		x;
	double		y;
	int			dist;
}				t_sprites;

typedef struct s_mov {
	int			left;
	int			right;
	int			up;
	int			down;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			mapx;
	int			mapy;
}				t_mov;

typedef struct s_camera {
	int			left;
	int			right;
	double		x;
}				t_camera;

typedef struct s_raycasting {
	double		dirx;
	double		diry;
	double		sidex;
	double		sidey;
	double		deltax;
	double		deltay;
	double		perp;
	int			stepx;
	int			stepy;
	double		step;
	int			hit;
	int			side;
	int			lineh;
	int			texnum;
	int			x;
	int			y;
	double		pos;
}				t_raycaster;

typedef struct s_draw {
	int			start;
	int			end;
	double		wallx;
	double		wally;
	int			repaint;
}				t_draw;

typedef struct s_check {
	int			res;
	int			texno;
	int			texso;
	int			texwe;
	int			texea;
	int			texsp;
	int			sky;
	int			floor;
	int			map;
	int			player;
}				t_check;

typedef struct s_cub {
	int			nrows;
	int			bmp;
	char		*line;
	char		**map;
	t_render	res;
	t_textures	tex;
	t_colors	col;
	t_minilix	libx;
	t_img		win;
	t_img		twall[MAX_TEXTURES];
	t_sprite	sp;
	t_sprites	*sprites;
	t_mov		mov;
	t_camera	cam;
	t_raycaster	ray;
	t_draw		draw;
	t_check		check;
}				t_cub;

void			info_tex(char *line, t_cub *info);
void			info_res(char *line, t_cub *info);
void			info_color(char *line, t_cub *info);
char			*info_map(char *line, char *stc, t_cub *cub);
void			search_player(t_cub *c);
void			init_struct(t_cub *info);
void			init_mlx_func(t_cub *c);
void			read_cub(char *filename, t_cub *info);
int				key_press_handler(int key, t_cub *c);
int				key_release_handler(int key, t_cub *c);
int				exit_handler(t_cub *c);
void			clean_exit(t_cub *c, char *str, int error);
int				paint_game(t_cub *c);
void			step_initial_side(t_cub *c);
int				move_keys(t_cub *c, double speed);
int				rotate_keys(t_cub *c, double speed);
int				raycaster(t_cub *c, int x);
void			init_sp_vble(t_cub *c);
void			init_raycast_vble(t_cub *info);
void			free_map(t_cub *c);
void			refill_map(t_cub *c);
int				draw(t_cub *c);
void			sprite2screen(t_cub *c);
void			search_sprites(t_cub *c);
void			my_mlx_pixel_put(t_cub *c, int x, int y, int color);
int				save_bmp(t_cub *c);
void			check_extension(char *filename);
int				check_resolution(char *num);
int				check_text(t_cub *c, char *text);
void			remove_spaces(char **line);
int				check_identifiers(t_cub *c);
int				is_texture(char *line);
int				error_tex_elements(char *line);
int				error_res_elements(char *line);
void			error_rgb_elements(t_cub *info, char *s);
void			check_map_wall(t_cub *c);
int				map_dimensions(t_cub *c);
int				count_sprites(t_cub *c);
void			ft_split(char const *s, char z, t_cub *c);
int				ft_isspace(char c);
int				all_textures(t_cub *c);
void			xpm2image(t_cub *c);
//void			free_stc_exit(t_cub *c, char *txt, char *stc);

#endif
