
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:27:07 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/21 19:27:07 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int			error_tex_elements(char *line)
{
	int i;
	int extension;

	extension = 0;
	i = 0;
	while (line[i] && line[i] != SPACE)
		i++;

	if (!ft_strncmp(&line[i-4], ".xpm", 4))
		extension = 1;

	while (line[i] && line[i] == SPACE)
		i++;

	if ((line[i-1] == SPACE && line[i] && extension) || !extension)
		return (1);
	return (0);
}

int			error_res_elements(char *line)
{
	int i;

	i = 0;
	if (line[i] == 'R')
		i++;
	while (line[i] && (ft_isdigit(line[i]) || line[i] == SPACE))
		i++;

	if (line[i])
		return (1);
	return (0);
}

void		error_rgb_elements(t_cub *info, char *s)
{
	int i;

	i = 0;
	if (s[i] == 'F' || s[i] == 'C')
		i++;
	while (s[i] && (ft_isdigit(s[i]) || s[i] == SPACE || s[i] == ','))
	{
		if (s[i] == ',' && !ft_isdigit(s[i+1]))
			clean_exit(info, "Invalid RGB format\n", 1);
		i++;
	}

	if (s[i])
	{
		if (s[0] == 'F')
		{
			//free(s);
			clean_exit(info, "Invalid characters in floor color\n", 1);
		}
		else if (s[0] == 'C')
			clean_exit(info, "Invalid characters in ceiling color\n", 1);
	}
}

static int	is_empty(char c)
{
	return (((int)c >= 9 && (int)c <= 13) || c == SPACE);
}

void		check_map_wall(t_cub *c)
{
	int x;
	int y;

	x = -1;
	while (c->map[++x])
	{
		y = -1;
		while (c->map[x][++y])
		{
			if (c->map[x][y] == EMPTY || c->map[x][y] == OBJECT)
			{
				if (is_empty(c->map[x-1][y-1]) || is_empty(c->map[x-1][y]) ||
					is_empty(c->map[x-1][y+1]) || is_empty(c->map[x][y-1]) ||
					is_empty(c->map[x][y+1]) || is_empty(c->map[x+1][y-1]) ||
					is_empty(c->map[x+1][y]) || is_empty(c->map[x+1][y+1]))
				{
					clean_exit(c, "The map must be surrounded by walls\n", 1);
				}
			}
		}
	}
}