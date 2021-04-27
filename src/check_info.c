/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:58:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 01:04:41 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	check_resolution(char *num)
{
	int	len;
	int	i;

	i = 0;
	while (num[i])
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			return (0);
		i++;
	}
	len = ft_strlen(num);
	if (len > MAX_LEN || !len)
		return (0);
	if (len == MAX_LEN && ft_strncmp(num, "214748364", 9) && num[len - 1] > '7')
		return (0);
	return (1);
}

int	check_text(t_cub *c, char *text)
{
	int	len;

	len = ft_strlen(text);
	if (c->tex.path_no && !ft_strncmp(c->tex.path_no, text, len))
		return (0);
	if (c->tex.path_so && !ft_strncmp(c->tex.path_so, text, len))
		return (0);
	if (c->tex.path_we && !ft_strncmp(c->tex.path_we, text, len))
		return (0);
	if (c->tex.path_ea && !ft_strncmp(c->tex.path_ea, text, len))
		return (0);
	if (ft_strncmp(&text[len - 4], ".xpm", 4))
		return (-1);
	return (1);
}

int	check_identifiers(t_cub *c)
{
	return (c->check.texno + c->check.texso + c->check.texwe
		+ c->check.texea + c->check.texsp + c->check.res
		+ c->check.floor + c->check.sky + c->check.map);
}

static void	player_dir(t_cub *c, int x, int y)
{
	c->mov.diry = 0.0;
	c->mov.dirx = 0.0;
	if (c->map[x][y] == NORTH)
		c->mov.dirx = -1.0;
	else if (c->map[x][y] == SOUTH)
		c->mov.dirx = 1.0;
	else if (c->map[x][y] == EAST)
		c->mov.diry = 1.0;
	else if (c->map[x][y] == WEST)
		c->mov.diry = -1.0;
	c->mov.planex = c->mov.diry * ((VIEW_ANGLE * M_PI) / 180);
	c->mov.planey = -c->mov.dirx * ((VIEW_ANGLE * M_PI) / 180);
}

void	search_player(t_cub *c)
{
	int	k;
	int	i;

	k = -1;
	while (c->map[++k])
	{
		i = -1;
		while (c->map[k][++i])
		{
			if (c->map[k][i] == NORTH || c->map[k][i] == SOUTH
			|| c->map[k][i] == WEST || c->map[k][i] == EAST)
			{
				c->mov.posx = k + 0.5;
				c->mov.posy = i + 0.5;
				player_dir(c, k, i);
				c->map[k][i] = EMPTY;
				c->check.player++;
			}
		}
	}
	if (!c->check.player)
		clean_exit(c, "Player not found\n", 1);
	if (c->check.player > 1)
		clean_exit(c, "Only one player allowed\n", 1);
}
