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
printf("cub1");
	read_cub(argv[1], &cub);
	printf("cub2");
	refill_map(&cub);
	printf("cub3");
	searchPlayer(&cub);
	printf("cub4");

	init_mlx_func(&cub);
	printf("cub5");

	if (argc == 3 && (!ft_strncmp(argv[2], "--save", 7)))
		return 1;	//save_bmp(&cub);	

printf("cub5");
	mlx_hook(cub.libx.window, 2, 1, key_handler, &cub);	// KEYPRESS
	printf("cub6");
	mlx_hook(cub.libx.window, 3, 3, key_handler, &cub);	// KEYRELESASE
	printf("cub7");
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, 0);	// CLOSE WINDOW
	printf("cub8");

	//mlx_put_image_to_window(cub.libx.mlx, cub.libx.window, cub.no.img, 50, 50);
	
	mlx_loop_hook(cub.libx.mlx, draw, &cub);			// RAYCASTING
	//mlx_loop_hook(cub.libx.mlx, raycaster, &cub);			// RAYCASTING

	mlx_loop(cub.libx.mlx);
	return (0);
}