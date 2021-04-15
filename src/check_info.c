/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:58:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 15:43:35 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"
#include "../inc/libft//printf.h"

/*static void comprobar_lecturaCub(t_cub cub)
{
	//printf("RESOLUCION x %d | y %d\n\r", cub.res.rend_x, cub.res.rend_y);
	//printf("TEXTURAS\nnorte: %s\nsur %s\noeste %s\neste %s\nsprite %s\n", 
	cub.tex.path_norte, cub.tex.path_sur, cub.tex.path_oeste, cub.tex.path_este, cub.tex.path_sprite);
	//printf("COLORES (RGB)\nsuelo %d %d %d\ntecho %d %d %d\n", cub.col.rgb_suelo[0], cub.col.rgb_suelo[1], cub.col.rgb_suelo[2],
	cub.col.rgb_techo[0], cub.col.rgb_techo[1], cub.col.rgb_techo[2]);
	int k = 0;
	while (cub.map[k])
	{
		int i = 0;
		while (cub.map[k][i])
		{
			//printf("%c", cub.map[k][i]);
			i++;
		}
		//printf("\n");
		k++;
	}
}*/

/*int		check_walls(t_cub cub)
{
	// Mapa debe estar rodeado por muros
	int i, j;

	i = 0;
	j = 0;

	while (cub.map[0][i] && cub.map[cub.nrows-1][j])
	{
		if (cub.map[0][i] != MURO || cub.map[cub.nrows-1][j] != MURO)
			return -1;

		i++;
		j++;
	}
	return 0;
}*/

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
}

// TODO: Comprobar que el mapa esté rodeado por muros