/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:58:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 19:57:09 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

// TODO: Comprobar que el mapa esté rodeado por muros
/*void check_walls(t_cub *c)
{

}*/

void check_extension(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		clean_exit(NULL, "Extensión de archivo incorrecta\n", 1);
}

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

