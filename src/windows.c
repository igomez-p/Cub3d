/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 18:20:06 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	paint(t_cub *c)
{
	int		x;
	int		y;

	y = 0;
	while (y < c->res.rend_y)
	{
		x = 0;
		while (x < c->res.rend_x)
		{
			c->win.data[y * c->res.rend_x + x] = 0x026600;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->libx.img, 0, 0);

	return (1);
}


