/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:27:07 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/30 17:56:37 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	error_tex_elements(char *line)
{
	int	i;
	int	k;
	int	count;

	count = 0;
	k = -1;
	i = 0;
	while (line[++k])
	{
		while (line[i] && line[i] != SPACE && line[i] != '\t')
			i++;
		if (line[i])
			count++;
		while (line[i] && (int)line[i] > 32 && (int)line[i] <= 126)
			i++;
	}
	if (count > 1)
		return (1);
	return (0);
}

int	error_res_elements(char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'R')
		i++;
	while (line[i] && (ft_isdigit(line[i]) || ft_isspace(line[i])))
		i++;
	if (line[i])
		return (1);
	return (0);
}

void	error_rgb_elements(t_cub *info, char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s[i] == 'F' || s[i] == 'C')
		i++;
	while (s[i] && (ft_isdigit(s[i]) || ft_isspace(s[i]) || s[i] == ','))
	{
		if (s[i] == ',' && !ft_isdigit(s[i + 1]))
			clean_exit(info, "Invalid RGB format\n", 1);
		if (s[i] == ',')
			count++;
		i++;
	}
	if (s[i] || count != 2)
	{
		if (s[0] == 'F')
			clean_exit(info, "Invalid RGB format in floor color\n", 1);
		else if (s[0] == 'C')
			clean_exit(info, "Invalid RGB format in ceiling color\n", 1);
	}
}

static int	is_empty(t_cub *c, int x, int y)
{
	if (x < 0 || y < 0 || x >= c->nrows)
		return (1);
	return (((int)c->map[x][y] >= 9 && (int)c->map[x][y] <= 13)
		|| c->map[x][y] == SPACE || !c->map[x][y]);
}

void	check_map_wall(t_cub *c)
{
	int	x;
	int	y;

	x = -1;
	while (c->map[++x])
	{
		y = -1;
		while (c->map[x][++y])
		{
			if (c->map[x][y] == EMPTY || c->map[x][y] == OBJECT
				|| c->map[x][y] == NORTH || c->map[x][y] == SOUTH
				|| c->map[x][y] == WEST || c->map[x][y] == EAST)
			{
				if (is_empty(c, x - 1, y - 1) || is_empty(c, x - 1, y)
					|| is_empty(c, x - 1, y + 1) || is_empty(c, x, y - 1)
					|| is_empty(c, x, y + 1) || is_empty(c, x + 1, y - 1)
					|| is_empty(c, x + 1, y) || is_empty(c, x, y + 1))
				{
					if (c->map[x][y] == EMPTY || c->map[x][y] == OBJECT)
						clean_exit(c, "Map must be surrounded by walls\n", 1);
					clean_exit(c, "The player must be inside the map\n", 1);
				}
			}
		}
	}
}
