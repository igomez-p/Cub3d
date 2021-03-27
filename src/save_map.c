/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:59:04 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/24 16:59:05 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		len_linea(char *line)
{
	int i;
	int cont;

	i = 0;
	cont = 0;
	while (line[i])
	{
		if (line[i] == VACIO || line[i] == MURO || line[i] == OBJETO || line[i] == NADA ||
			line[i] == 'N' || line[i] == 'S' || line[i] == 'O' || line[i] == 'E')
			cont++;
		i++;
	}
	return (cont);
}

char	*fill_map(char *line)
{
	char	*aux;
	int		p;
	int		k;

	p = 0;
	k = len_linea(line);
	if ((int)ft_strlen(line) == k)
		return (ft_strdup(line));
	else
		aux = malloc(k + 1);
	if (!aux)
		return (NULL);
	k = 0;
	while (line[p])
	{
		if (line[p] == VACIO || line[p] == MURO || line[p] == OBJETO || line[p] == NADA ||
			line[p] == 'N' || line[p] == 'S' || line[p] == 'O' || line[p] == 'E')
		{
			aux[k] = line[p];
			k++;
		}
		p++;
	}
	aux[k] = '\0';
	return (aux);
}

char	*info_map(char *line, char *stc)
{
	char	*aux;

	if (!stc)
		stc = fill_map(line);
	else
	{
		aux = fill_map(line);
		stc = ft_swap(stc, aux);
		free(aux);
	}
	return (stc);
}

int		check_errors(t_cub cub)
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
}

void searchPlayer(t_cub *cub)
{
	int k = 0;
	while (cub->map[k])
	{
		int i = 0;
		while (cub->map[k][i])
		{
			if (cub->map[k][i] == NORTE || cub->map[k][i] == SUR || cub->map[k][i] == OESTE || cub->map[k][i] == ESTE)
			{
				cub->player.x = k;
				cub->player.y = i;
				cub->player.dir = cub->map[k][i];
				printf("(%d, %d) - %c\n\r", cub->player.x, cub->player.y, cub->player.dir);
				return ;
			}
			i++;
		}
		k++;
	}
}