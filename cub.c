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
		if (linea != NULL && ft_strchr(linea, '1'))
			stc_line = info_map(linea, stc_line);
		info->map = ft_split(stc_line, '\n');
		close (fd);
	}
}

static void comprobar_lecturaCub(t_cub cub)
{
	printf("RESOLUCION x %d | y %d\n\r", cub.res.rend_x, cub.res.rend_y);
	printf("TEXTURAS\nnorte: %s\nsur %s\noeste %s\neste %s\nsprite %s\n", 
	cub.tex.path_no, cub.tex.path_so, cub.tex.path_we, cub.tex.path_ea, cub.tex.path_sp);
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
	t_cub	cub;
	init_struct(&cub);

	if (argc < 2)
	{
		clean_exit(&cub, "Numero de argumentos invalido\n", 1);
		return (-1);
	}

	read_cub(argv[1], &cub);
	comprobar_lecturaCub(cub);
	refill_map(&cub);
	searchPlayer(&cub);

	comprobar_lecturaCub(cub);

	printf("holaa\n");

	init_mlx_func(&cub);

	if (argc == 3 && (!ft_strncmp(argv[2], "--save", 7)))
		return 1;	//save_bmp(&cub);	

	mlx_hook(cub.libx.window, 2, 1u << 0, key_handler, &cub);	// KEYPRESS
	mlx_hook(cub.libx.window, 3, 1u << 1, key_handler, &cub);	// KEYRELESASE
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, &cub);	// CLOSE WINDOW
	
	mlx_loop_hook(cub.libx.mlx, draw, &cub);			// RAYCASTING

	mlx_loop(cub.libx.mlx);
	return (0);
}