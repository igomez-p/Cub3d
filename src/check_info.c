/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:58:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 20:43:35 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

// TODO: Comprobar que el mapa esté rodeado por muros
/*void check_walls(t_cub *c)
{

}*/

int check_resolution(char *num)
{
	int len;
	int i;

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

int check_text(t_cub *c, char *text)
{
	int len;

	len = ft_strlen(text);
	if (c->tex.path_no && !ft_strncmp(c->tex.path_no, text, len))
		return (0);
	if (c->tex.path_so && !ft_strncmp(c->tex.path_no, text, len))
		return (0);
	if (c->tex.path_we && !ft_strncmp(c->tex.path_no, text, len))
		return (0);
	if (c->tex.path_ea && !ft_strncmp(c->tex.path_no, text, len))
		return (0);
	
	if (ft_strncmp(&text[len - 4], ".xpm", 4))
		return (-1);

	return (1);
}

int check_identifiers(t_cub *c)
{
	return (c->check.texno + c->check.texso + c->check.texwe + 
			c->check.texea + c->check.texsp + c->check.res +
			c->check.floor + c->check.sky + c->check.map);
}

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == NADA)
		i++;

	if (line[i])
		return (0);
	return (1);
}