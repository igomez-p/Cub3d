/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:59:04 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/17 15:07:49 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

#define VIEW_ANGLE	32.5

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
		else
			return (-1);
		i++;
	}
	return (cont);
}

static char	*fill_map(char *line)
{
	char	*aux = NULL;
	int		p;
	int		k;

	p = 0;
	if ((k = len_linea(line)) == -1)
		return NULL;
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
	aux[k+1] = '\0';
	return (aux);
}

char	*info_map(char *line, char *stc, t_cub *cub)
{
	char	*aux;

	if (!stc)
	{
		stc = fill_map(line);
		if (!stc)
			clean_exit(cub, "Mapa incorrecto\n", 1);
		return (stc);
	}
	aux = fill_map(line);
	if (!aux)
		clean_exit(cub, "Mapa incorrecto\n", 1);

	stc = ft_swap(stc, aux);
	free(aux);

	return (stc);
}

static void player_dir(t_cub *c, int x, int y)
{
	c->mov.diry = 0.0;
	c->mov.dirx = 0.0;
	if (c->map[x][y] == NORTE)
		c->mov.dirx = -1.0;
	else if (c->map[x][y] == SUR)
		c->mov.dirx = 1.0;
	else if (c->map[x][y] == ESTE)
		c->mov.diry = 1.0;
	else if (c->map[x][y] == OESTE)
		c->mov.diry = -1.0;

	c->mov.planex = c->mov.diry * ((VIEW_ANGLE * M_PI) / 180);
	c->mov.planey = -c->mov.dirx * ((VIEW_ANGLE * M_PI) / 180);
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
				cub->map[k][i] = VACIO;
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

	i = c->nrows;
	if (c->map)
	{
		while (i > 0) {
			free(c->map[i]);
			i--;
		}

		free(c->map);
	}
}

void refill_map(t_cub *c)
{
	int w = map_dimensions(c);
	char **map = malloc((c->nrows+1)*sizeof(char *));
	int k = 0;
	while (c->map[k])
	{
		map[k] = malloc((w+1)*sizeof(char));
		int len = ft_strlen(c->map[k]);
		ft_memcpy(map[k], c->map[k], len);
		if (len < w)
			ft_memset(&map[k][len], ' ', w-len);

		map[k][w] = '\0';
		k++;
	}
	map[k] = NULL;
	free_map(c);
	c->map = map;
}
