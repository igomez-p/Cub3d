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

static int	len_linea(char *line)
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

static char	*fill_map(char *line)
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

static void player_dir(t_cub *c, int x, int y)
{
	// TODO: comprobar si esta bien la logica
	if (c->map[x][y] == NORTE)
		c->mov.diry = 1.0;
	else if (c->map[x][y] == SUR)
		c->mov.diry = -1.0;
	else if (c->map[x][y] == ESTE)
		c->mov.dirx = 1.0;
	else if (c->map[x][y] == OESTE)
		c->mov.dirx = -1.0;

	c->mov.planex = c->mov.diry * -0.66;
	c->mov.planey = c->mov.dirx * 0.66;
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
				cub->mov.posx = k + 0.5;
				cub->mov.posy = i + 0.5;
				player_dir(cub, k, i);
				return ;
			}
			i++;
		}
		k++;
	}
	clean_exit(cub, "No se encuentra jugador\n", 1);
}

static int map_dimensions(t_cub *c)
{
	int max = ft_strlen(c->map[0]);
	int i = 1;
	int len = 0;
	while (c->map[i])
	{
		len = ft_strlen(c->map[i]);
		if (len > max)
			max = len;

		i++;
	}
	c->nrows = i;
	return max;
}

void free_map(t_cub *c)
{
	int i;

	i = 0;
	if (c->map)
	{
		while (c->map[i]) {
			printf("a11\n");
			free(c->map[i++]);
		}

printf("a3\n");
		c->map = NULL;
	}
}

void refill_map(t_cub *c)
{
	int w = map_dimensions(c);
	char **map = malloc(c->nrows);
	int k = 0;
	while (c->map[k])
	{
		map[k] = malloc(w);
		int len = ft_strlen(c->map[k]);
		memcpy(map[k], c->map[k], len);
		if (len < w)
			memset(&map[k][len], ' ', w-len);
		
		k++;
	}
	free_map(c);
	printf("free map ok\n");
	c->map = &map[0];
}