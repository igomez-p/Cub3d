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

/*void	char_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->win.addr + (y * cub->win.sz + x * (cub->win.bpp / 8));
	*(unsigned int*)dst = color;
}*/

void	paint_sky_floor(t_cub *c)
{
	int		x;
	int		y;

	y = -1;
	while (++y < c->win.hei)
	{
		x = -1;
		while (++x < c->win.wid)
		{
			if (y < c->win.hei/2)
				mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, 0xff0055);	// sky
			else
				mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, 0xaa6611);	// floor
		}
	}
}

/*void paint_sky(t_cub *c, int x)
{
	int y;

	y = -1;
	while (++y < c->draw.start)
		mlx_pixel_put(c->libx.mlx, c->libx.window, x, y, 0x00aa00);
}*/

int draw(t_cub *c)
{
	int x;

	x = -1;
	paint_screen_floor(c);
	while (++x < c->win.wid)
	{
		raycaster(c, x);
		//paint_sky(c, x);
	}
	//mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->win.img, 0, 0);
	move_keys(c, 1);
	rotate_keys(c, 1);
	return (1);
}
