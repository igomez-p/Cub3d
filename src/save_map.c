/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:59:04 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/30 17:05:12 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	is_char_valid(char c)
{
	return (c == EMPTY || c == WALL || c == OBJECT || ft_isspace(c)
		|| c == NORTH || c == WEST || c == SOUTH || c == EAST);
}

static int	len_line(char *line)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (line[i])
	{
		if (is_char_valid(line[i]))
			cont++;
		else
			return (-1);
		i++;
	}
	return (cont);
}

static char	*fill_map(char *line)
{
	char	*aux;
	int		p;
	int		k;

	aux = NULL;
	k = len_line(line);
	if (k == -1)
		return (NULL);
	if ((int)ft_strlen(line) == k)
		return (ft_strdup(line));
	else
		aux = (char *)malloc(sizeof(char)*(k + 1));
	if (!aux)
		return (NULL);
	p = -1;
	k = -1;
	while (line[++p])
	{
		if (line[p])
			aux[++k] = line[p];
	}
	aux[k + 1] = '\0';
	return (aux);
}

char	*info_map(char *line, char *stc, t_cub *cub)
{
	char	*aux;

	if (!stc)
	{
		stc = fill_map(line);
		if (!stc)
			clean_exit(cub, "Wrong map\n", 1);
		return (stc);
	}
	aux = fill_map(line);
	if (!aux)
		clean_exit(cub, "Wrong map\n", 1);
	stc = ft_swap(stc, aux);
	free(aux);
	return (stc);
}

int	map_dimensions(t_cub *c)
{
	int	max;
	int	i;
	int	len;

	max = ft_strlen(c->map[0]);
	i = 1;
	len = 0;
	while (c->map[i])
	{
		len = ft_strlen(c->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	c->nrows = i;
	return (max);
}
