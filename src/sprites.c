/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:09:50 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 11:40:41 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static void	sort_sprite(t_cub *c)
{
	int			s;
	int			z;
	int			total;
	t_sprites	tmp;

	total = count_sprites(c);
	s = -1;
	while (++s < total)
	{
		z = -1;
		while (++z < total)
		{
			if (c->sprites[s].dist > c->sprites[z].dist)
			{
				tmp = c->sprites[s];
				c->sprites[s] = c->sprites[z];
				c->sprites[z] = tmp;
			}
		}
	}
}

void	search_sprites(t_cub *c)
{
	int	x;
	int	y;
	int	s;

	c->sprites = malloc(sizeof(t_sprite) * (count_sprites(c)));
	s = 0;
	x = -1;
	while (c->map[++x])
	{
		y = -1;
		while (c->map[x][++y])
		{
			if (c->map[x][y] == OBJECT)
			{
				c->sprites[s].x = x + 0.5;
				c->sprites[s].y = y + 0.5;
				c->sprites[s].dist = ((c->mov.posx - c->sprites[s].x)
						* (c->mov.posx - c->sprites[s].x) + (c->mov.posy
							- c->sprites[s].y) * (c->mov.posy
							- c->sprites[s].y));
				s++;
			}
		}
	}
}

static void	sp_draw(t_cub *c)
{
	c->sp.draw_starty = -c->sp.h / 2 + c->win.hei / 2;
	if (c->sp.draw_starty < 0)
		c->sp.draw_starty = 0;
	c->sp.draw_endy = c->sp.h / 2 + c->win.hei / 2;
	if (c->sp.draw_endy >= c->win.hei)
		c->sp.draw_endy = c->win.hei - 1;
	c->sp.draw_startx = -c->sp.w / 2 + c->sp.screenx;
	if (c->sp.draw_startx < 0)
		c->sp.draw_startx = 0;
	c->sp.draw_endx = c->sp.w / 2 + c->sp.screenx;
	if (c->sp.draw_endx >= c->win.wid)
		c->sp.draw_endx = c->win.wid - 1;
}

static void	sprite_loop(t_cub *c, double ty)
{
	int	x;
	int	y;
	int	texx;
	int	texy;
	int	d;

	x = c->sp.draw_startx - 1;
	while (++x < c->sp.draw_endx)
	{
		texx = (int)(BYTE * (x - (-c->sp.w / 2 + c->sp.screenx))
				* c->sp.wid / c->sp.w) / BYTE;
		if (ty >= 0 && x >= 0 && x <= c->win.wid && ty < c->sp.zbuf[x])
		{
			y = c->sp.draw_starty - 1;
			while (++y < c->sp.draw_endy)
			{
				d = y * BYTE - c->win.hei * (BYTE / 2) + c->sp.h * (BYTE / 2);
				texy = abs(((d * c->sp.hei) / c->sp.h) / BYTE);
				c->sp.color = c->sp.addr[c->sp.wid * texy + texx];
				if ((c->sp.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(c, x, y, c->sp.color);
			}
		}
	}
}

void	sprite2screen(t_cub *c)
{
	double	idet;
	double	tx;
	double	ty;
	int		s;
	int		total;

	total = count_sprites(c);
	s = -1;
	free(c->sprites);
	search_sprites(c);
	sort_sprite(c);
	while (++s < total)
	{
		c->sp.posx = (double)c->sprites[s].x - c->mov.posx;
		c->sp.posy = (double)c->sprites[s].y - c->mov.posy;
		idet = 1.0 / (c->mov.planex * c->mov.diry - c->mov.dirx
				* c->mov.planey);
		tx = idet * (c->mov.diry * c->sp.posx - c->mov.dirx * c->sp.posy);
		ty = idet * (-c->mov.planey * c->sp.posx + c->mov.planex * c->sp.posy);
		c->sp.screenx = (int)((c->win.wid / 2) * (1 + tx / ty));
		c->sp.h = abs((int)(c->win.hei / ty));
		c->sp.w = abs((int)(c->win.hei / ty));
		sp_draw(c);
		sprite_loop(c, ty);
	}
}
