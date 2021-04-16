/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/16 18:30:41 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static int rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	paint_sky_floor(t_cub *c)
{
	int	x;
	int	y;
	int	sky_color;
	int	floor_color;

	sky_color = rgb2int(c->col.rgb_s[0], c->col.rgb_s[1], c->col.rgb_s[2]);
	floor_color = rgb2int(c->col.rgb_f[0], c->col.rgb_f[1], c->col.rgb_f[2]);
	y = -1;
	while (++y < c->win.hei)
	{
		x = -1;
		while (++x < c->win.wid)
		{
			if (y < c->win.hei/2)
				mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, sky_color);
			else
				mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, floor_color);
		}
	}
}

int draw(t_cub *c)
{
	int x;

	x = -1;
	paint_sky_floor(c);
	while (++x < c->win.wid)
	{
		raycaster(c, x);
		//move_keys(c, SQUARES_SEC);
		//rotate_keys(c, RADIANS_SEC);
	}
	move_keys(c, SQUARES_SEC);
	rotate_keys(c, RADIANS_SEC);
	return (1);
}
