/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:51:44 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 19:48:43 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define NADA ' '
# define VACIO '0'
# define MURO '1'
# define OBJETO '2'
# define NORTE	'N'
# define SUR	'S'
# define OESTE	'w'
# define ESTE	'E'
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# include "libft.h"
# include "libftprintf.h"
# include "/usr/local/include/mlx.h"

#define PASO 0.01
#define GRADOS2RADIAN(angle) ((angle) / 180.0 * M_PI)

#define KEY_A_ 'a'   //97
#define KEY_S_ 's'   //115
#define KEY_D_ 'd'   //100
#define KEY_W_ 'w'   //119
#define KEY_LEFT_  65361
#define KEY_RIGHT_ 65363
#define KEY_SPACE_ 32
#define KEY_ESC_   65307

#ifdef	MAC_SYSTEM
	# include "keycode_mac.h"
#elif	LINUX_SYSTEM
	# include "keycode_linux.h"
#endif

typedef struct	s_resolucion {
				int rend_x;
				int rend_y;
}				t_resolucion;

typedef struct	s_img_tex {
				void *img;
				int *addr;
				int hei;
				int wid;
				int sz;
				int endian;
				int bpp;
} t_img_tex;

typedef struct	s_texturas {
				char *path_no;
				char *path_so;
				char *path_we;
				char *path_ea;
				char *path_sp;
}				t_texturas;

typedef struct	s_colores {
				int rgb_suelo[3];
				int rgb_techo[3];
}				t_colores;

typedef struct	mlx_img_list_s
{
  int			width;
  int			height;
  char			*buffer;
  float			vertexes[8];
  struct mlx_img_list_s	*next;
} mlx_img_list_t;

typedef struct	s_minilibx {
				void	*mlx;
				void	*window;
				void	*img;
				int		height;
				int		width;
}				t_minilix;

typedef struct	s_window {
				int sz_line;
				int endian;
				int bpp;
				int *data;
}				t_window;

typedef struct	s_mov {
				int left;
				int right;
				int up;
				int down;
				int x;
				int y;
				float dirx;
				float diry;
				float angle;
				float v;
				float turn;
}				t_mov;

typedef struct	s_camera {
				int left;
				int right;
}				t_camera;

typedef struct	s_raycasting {
				float alt_ant;
				float ntecho_ant;
				float nsuelo_ant;
				float last_time;
				float delta;
}				t_raycasting;

typedef struct	s_cub {
				t_resolucion res;
				t_texturas tex;
				t_colores col;
				char **map;
				int	nrows;
				t_minilix libx;
				t_window	win;
				t_mov		player;
				t_camera	cam;
				t_raycasting ray;
				t_img_tex no;
				t_img_tex so;
				t_img_tex ea;
				t_img_tex we;
				t_img_tex sp;

				int	resz_map;
				int resz_player;
}				t_cub;

void			info_tex(char *line, t_cub *info);
void			info_res(char *line, t_cub *info);
void			info_color(char *line, t_cub *info);
char			*info_map(char *line, char *stc);
void			searchPlayer(t_cub *cub);
void			init_struct(t_cub *info);
void    		init_mlx_func(t_cub *c);
void			read_cub(char *filename, t_cub *info);
int				key_handler(int key, t_cub *c);
int				exit_handler(t_cub *c);
void			clean_exit(t_cub *c, char *str, int error);
int 			paint_game(t_cub *c);

void			eliminarEspacios(t_cub *cub);
int				paint(t_cub *c);
int				render_map(t_cub *c);
int				draw(t_cub *c);

#endif
