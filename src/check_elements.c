
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

int	error_tex_elements(char *line)
{
	int i;
	int extension;

	extension = 0;
	i = 0;
	while (line[i] && line[i] != SPACE)
		i++;
	
	if (line[i-4] == '.' && line[i-3] == 'x' && line[i-2] == 'p' && line[i-1] == 'm')
		extension = 1;
	
	while (line[i] && line[i] == SPACE)
		i++;
	
	if ((line[i-1] == SPACE && line[i] && extension) || !extension)
		return (1);
	return (0);
}

int error_res_elements(char *line)
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

void error_rgb_elements(t_cub *info, char *line)
{
    int i;

    i = 0;
    if (line[i] == 'F' || line[i] == 'C')
        i++;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == SPACE || line[i] == ','))
    {
        if (line[i] == ',' && !ft_isdigit(line[i+1]))
            clean_exit(info, "Invalid RGB format\n", 1);
        i++;
    }

    if (line[i])
    {
        if (line[0] == 'F')
        {
            //free(line);
            clean_exit(info, "Invalid characters in floor color\n", 1);
        }
        else if (line[0] == 'C')
            clean_exit(info, "Invalid characters in ceiling color\n", 1);
    }
}

static int ft_isspace(char c)
{
    return (((int)c >= 9 && (int)c <= 13) || c == SPACE);
}

void check_map_wall(t_cub *c)
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
                if (ft_isspace(c->map[x-1][y-1]) || ft_isspace(c->map[x-1][y]) ||
                    ft_isspace(c->map[x-1][y+1]) || ft_isspace(c->map[x][y-1]) ||
                    ft_isspace(c->map[x][y+1]) || ft_isspace(c->map[x+1][y-1]) ||
                    ft_isspace(c->map[x+1][y]) || ft_isspace(c->map[x+1][y+1]))
                {
                    clean_exit(c, "The map must be surrounded by walls\n", 1);
                }
            }
        }
    }
}