
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:09:50 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/17 15:34:25 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

#define U_DIV	1
#define V_DIV	1
#define V_MOVE	0.0
#define BYTE	256

static void sp_draw(t_cub *c, int height, int width, int screenx)
{
	c->sp.draw_starty = -height / 2 + c->win.hei / 2;
	if (c->sp.draw_starty < 0)
		c->sp.draw_starty = 0;
	c->sp.draw_endy = height / 2 + c->win.hei / 2;
	if (c->sp.draw_endy >= c->win.hei)
		c->sp.draw_endy = c->win.hei - 1;

	c->sp.draw_startx = -width / 2 + screenx;
	if (c->sp.draw_startx < 0)
		c->sp.draw_startx = 0;
	c->sp.draw_endx = width / 2 + screenx;
	if (c->sp.draw_endx >= c->win.wid)
		c->sp.draw_endx = c->win.wid - 1;
}

static void sprite_loop(t_cub *c, int width, int screenx, int transfy, int height,double *zbuf)
{
	int x;
	int y;
	int texx;
	int texy;
	int d;
	int color;

	x = c->sp.draw_startx - 1;
	while (++x < c->sp.draw_endx)
	{
		texx = (int)(BYTE * (x - (-width / 2 + screenx)) * c->sp.wid / width) / BYTE;
		if (transfy > 0 && x > 0 && x < c->win.wid && transfy < zbuf[x])
		{
			y = c->sp.draw_starty - 1;
			while (++y < c->sp.draw_endy)
			{
				d = y * BYTE - c->win.hei * (BYTE/2) + height * (BYTE/2);
				texy = abs(((d * c->sp.hei) / height) / BYTE);
				color = c->sp.addr[c->sp.wid * texy + texx];
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(c, x, y, color);
			}
		}
	}
}

static void scaling_sprite(t_cub *c, double transformy, double transformx, double *zbuf)
{
	int sprite_screenx;
	int sp_height;
	int sp_width;

	sprite_screenx = (int)((c->win.wid / 2) * (1 + transformx / transformy));
	sp_height = abs((int)(c->win.hei / transformy)) / V_DIV;
	sp_width = abs((int)(c->win.hei / transformy)) / U_DIV;
	sp_draw(c, sp_height, sp_width, sprite_screenx);
	sprite_loop(c, sp_width, sprite_screenx, transformy, sp_height, zbuf);
}

void sprite2screen(t_cub *c, double *zbuf)
{
	double inv_det;
	double transformx;
	double transformy;


	c->sp.posx = c->sp.x - c->mov.posx;
	c->sp.posy = c->sp.y - c->mov.posy;

	inv_det = 1.0 / (c->mov.planex * c->ray.diry - c->ray.dirx * c->mov.planey);
	transformx = inv_det * (c->ray.diry * c->sp.posx - c->ray.dirx * c->sp.posy);
	transformy = inv_det * (-c->mov.planey * c->sp.posx + c->mov.planex * c->sp.posy);
	scaling_sprite(c, transformy, transformx, zbuf);
}
