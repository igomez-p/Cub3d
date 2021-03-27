/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:58:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 15:43:35 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"
#include "../inc/libftprintf.h"

void	check_error(t_cub *c, char *str)
{
	//int		i;
	int		len;

	len = ft_strlen(str);
	write(1, "Error\n", 6);
	if (!str)
		perror("");
	else
		write(1, str, len);

	//i = -1;
	/*if (c->map)
	{
		while (++i < c->nrows)
			free(c->map[i]);
		free(c->map);
	}*/
//	if (t->fd > 0)
//		close(t->fd);
	if (c->libx.window)
		mlx_destroy_window(c->libx.mlx, c->libx.window);
	if (c->libx.mlx)
		mlx_destroy_image(c->libx.mlx, c->libx.img);
	exit(1);
}
