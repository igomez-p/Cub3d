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

#define	MAC_SYSTEM		0
#define LINUX_SYSTEM	1

#ifdef	MAC_SYSTEM
	# include "keycode_mac.h"
#elif	LINUX_SYSTEM
	# include "keycode.h" //"keycode_linux.h"
#else
	# include "keycode.h"
#endif

// open, read, write, malloc, free, perror, strerror, exit
// librería math y minilib

/*
INFORMACIÓN TIPO DE ESCENA archivo .cub

- Se puede separar cada tipo de elemento con una o varias líneas vacías
- Los elementos, excepto el map, pueden ir colocados en cualquier orden
- Problemas config archivo -> "Error\n" + mensaje explícito a elegir

- Resolución:		R [tam renderizado eje x] [tam renderizado eje y]
- Textura norte:	NO ./path_textura_norte
- Textura sur:		SO ./path_textura_sur
- Textura oeste:	WE ./path_textura_oeste
- Textura este:		EA ./path_textura_este
- Textura sprite:	S ./path_textura_sprite
- Color suelo:		F [R,G,B en rango (0,255)]
- Color techo:		C [R,G,B en rango (0,255)]
- map
	- 0: espacios vacíos
	- 1: muros
	- 2: objeto
	- N, S, E o W: posición inicial jugador y orientación
	- Debe estar encerrado/rodeado por muros, si no error
	- Siempre al final del archivo .cub
	- Info de cada elemento puede ir separada por uno o varios espacios

TECLAS

- teclado izq y dcha -> rotar cámara
- W, A, S y D -> desplazar cámara (personaje)
- ESC y/o clic sobre aspa roja -> cerrar ventana, salir del programa limpiamente
- Tamaño ventana pedida en map > pantalla ? Limitar tamaño ventana a la pantalla

*/
typedef struct	s_resolucion {
				int rend_x;
				int rend_y;
}				t_resolucion;

typedef struct	s_texturas {
				char *path_norte;
				char *path_sur;
				char *path_oeste;
				char *path_este;
				char *path_sprite;
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
				char dir; // dirección jugador (N, W, E o S)
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

				int	resz_map;
				int resz_player;
}				t_cub;

void			info_tex(char *line, t_cub *info);
void			info_res(char *line, t_cub *info);
void			info_color(char *line, t_cub *info);
char			*info_map(char *line, char *stc);
void			searchPlayer(t_cub *cub);
void			init_struct(t_cub *info);
void			read_cub(char *filename, t_cub *info);
void			eliminarEspacios(t_cub *cub);
void			check_error(t_cub *c, char *str);
int				exit_handler(t_cub *c);
int				paint(t_cub *c);
int				render_map(t_cub *c);
int				draw(t_cub *c);
int key_handler(int key, t_cub *c);

#endif
