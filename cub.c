/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 19:48:01 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub.h"


// Función para leer archivo .cub
void	read_cub(char *filename, t_cub *info)
{
	int	fd;
	char	*linea;
	char	*stc_line;

	stc_line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		perror("Error\nFallo al abrir el archivo\n");
	else
	{
		linea = 0;
		while (get_next_line(fd, &linea) > 0)
		{
			//Puede haber espacios antes de un identificador?? en ese caso, mover puntero hasta el 1er char alpha
			if (ft_strchr(linea, 'R'))
				info_res(linea, info);
			else if (!ft_strncmp(linea, "NO", 2) || !ft_strncmp(linea, "SO", 2) ||
					!ft_strncmp(linea, "WE", 2) || !ft_strncmp(linea, "EA", 2) ||
					!ft_strncmp(linea, "S", 1))
				info_tex(linea, info);
			else if (ft_strchr(linea, 'F') || ft_strchr(linea, 'C'))
				info_color(linea, info);
			else if (ft_strchr(linea, '1'))
			{
				stc_line = info_map(linea, stc_line);
				stc_line = ft_swap(stc_line, "\n");
			}
			free(linea);
			linea = 0;
		}
		if (!get_next_line(fd, &linea) && ft_strchr(linea, '1'))
			stc_line = info_map(linea, stc_line);
		info->map = ft_split(stc_line, '\n');
	}
}

void eliminarEspacios(t_cub *cub)
{
    char **map_aux = NULL;
    int filas = 0, colum = 0, y = 0, x = 0;
    while (cub->map[filas])
    {
        while (cub->map[filas][colum])
        {
            if (cub->map[filas][colum] != NADA)
            {
                map_aux[y][x] = cub->map[filas][colum];
                x++;
            }
            colum++;
        }
        y++;
        filas++;
    }
	cub->nrows = filas;
    cub->map = map_aux;
   // mapaColum = x;
   // mapaFilas = y;
}

static void comprobar_lecturaCub(t_cub cub)
{
	printf("RESOLUCION x %d | y %d\n\r", cub.res.rend_x, cub.res.rend_y);
	printf("TEXTURAS\nnorte: %s\nsur %s\noeste %s\neste %s\nsprite %s\n", 
	cub.tex.path_norte, cub.tex.path_sur, cub.tex.path_oeste, cub.tex.path_este, cub.tex.path_sprite);
	printf("COLORES (RGB)\nsuelo %d %d %d\ntecho %d %d %d\n", cub.col.rgb_suelo[0], cub.col.rgb_suelo[1], cub.col.rgb_suelo[2],
	cub.col.rgb_techo[0], cub.col.rgb_techo[1], cub.col.rgb_techo[2]);
	int k = 0;
	while (cub.map[k])
	{
		int i = 0;
		while (cub.map[k][i])
		{
			printf("%c", cub.map[k][i]);
			i++;
		}
		printf("\n");
		k++;
	}
}

int		main(int argc, char *argv[])
{
	// argumento 1: archivo rt con info sobre el elemento
	// argumento 2: --save

	if (argc < 2)
	{
		perror("Error\nNumero de argumentos invalido\n");
		return (-1);
	}

	t_cub	cub;
	init_struct(&cub);
	read_cub("maps/prueba.map", &cub);
	comprobar_lecturaCub(cub);
	searchPlayer(&cub);

	if (!(cub.libx.mlx = mlx_init()))
		check_error(&cub, "Error al inicializar MLX\n");

	if(!(cub.libx.window = mlx_new_window(cub.libx.mlx, cub.res.rend_x, cub.res.rend_y, "Cub3D")))
		check_error(&cub, "Error new window\n");
	if (!(cub.libx.img = mlx_new_image(cub.libx.mlx, cub.res.rend_x, cub.res.rend_y)))
		check_error(&cub, "Error new image\n");

	cub.win.data = (int *)mlx_get_data_addr(cub.libx.img, &cub.win.bpp, &cub.win.sz_line, &cub.win.endian);

	if (argc == 3 && (!ft_strncmp(argv[2], "--save", 7)))
		return 1;	//save_bmp(&cub);

cub.libx.img = mlx_xpm_file_to_image(cub.libx.mlx, cub.tex.path_sprite, &cub.res.rend_x, &cub.res.rend_y);	// Para cargar las texturas desde xpm
	
	if (cub.libx.img)
		mlx_put_image_to_window(cub.libx.mlx, cub.libx.window, cub.libx.img, 0, 0);

	mlx_do_key_autorepeatoff(cub.libx.mlx);
// raycast();
	//if (!cub.win.bpp)
	//{
		printf("entra\n\r");
		mlx_hook(cub.libx.window, 2, 1, key_handler, &cub);	// KEYPRESS
		mlx_hook(cub.libx.window, 3, 3, key_handler, &cub);	// KEYRELESASE
		mlx_hook(cub.libx.window, 17, 0, exit_handler, 0);	// CLOSE WINDOW
		//mlx_loop_hook(cub.libx.mlx, draw, &cub);			// RAYCASTING
	//}

	mlx_loop(cub.libx.mlx);
	return (0);
}