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

int	paint_screen(t_cub *c)
{
	int		x;
	int		y;

	y = -1;
	while (++y < c->win.hei)
	{
		x = -1;
		while (++x < c->win.wid)
			mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, 0xff0055);
			//c->win.addr[y * c->win.sz + x * (c->win.bpp / 8)] = 0xff0055; // SEGFAULT
	}

	return (1);
}

int draw(t_cub *c)
{
	int x;

	x = -1;
	paint_screen(c);
	while (++x < c->win.wid)
	{
		raycaster(c, x);
	}
	mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->win.img, 0, 0);
	move_keys(c, 1);
	rotate_keys(c, 1);
	return (1);
}
