/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 19:08:48 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub.h"


static void comprobar_lecturaCub(t_cub cub)
{
	/*printf("RESOLUCION x %d | y %d\n\r", cub.res.rend_x, cub.res.rend_y);
	printf("TEXTURAS\nnorte: %s\nsur %s\noeste %s\neste %s\nsprite %s\n",
	cub.tex.path_no, cub.tex.path_so, cub.tex.path_we, cub.tex.path_ea, cub.tex.path_sp);
	printf("COLORES (RGB)\nsuelo %d %d %d\ntecho %d %d %d\n", cub.col.rgb_f[0], cub.col.rgb_f[1], cub.col.rgb_f[2],
	cub.col.rgb_s[0], cub.col.rgb_s[1], cub.col.rgb_s[2]);*/
	int k = 0;
	while (cub.map[k])
	{
		int i = 0;
		while (cub.map[k][i])
		{
			//printf("%c", cub.map[k][i]);
			i++;
		}
		//printf("|\n");
		k++;
	}
	//printf("sale\n");
}

int		main(int argc, char *argv[])
{
	t_cub	cub;
	init_struct(&cub);

	if (argc < 2)
	{
		clean_exit(&cub, "Numero de argumentos invalido\n", 1);
		return (-1);
	}
	check_extension(argv[1]);
	read_cub(argv[1], &cub);
	comprobar_lecturaCub(cub);
	refill_map(&cub);
	searchPlayer(&cub);
	search_sprites(&cub);

	comprobar_lecturaCub(cub);

	if (argc == 3 && (!ft_strncmp(argv[2], "--save", 7)))
		save_bmp(&cub);

	init_mlx_func(&cub);
	mlx_hook(cub.libx.window, 2, 0, key_press_handler, &cub);
	mlx_hook(cub.libx.window, 3, 0, key_release_handler, &cub);
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, &cub);
	mlx_loop_hook(cub.libx.mlx, draw, &cub);

	mlx_loop(cub.libx.mlx);
	return (0);
}
