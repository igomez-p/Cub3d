
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

static int	count_sprites(t_cub *c)
{
	int x;
	int y;
	int count;

	count = 0;
	x = 0;
	while (c->map[x])
	{
		y = 0;
		while (c->map[x][y])
		{
			if (c->map[x][y] == OBJETO)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

static void	sort_sprite(t_cub *c)
{
	int s;
	int z;
	int total;
	t_sprites tmp;

	total = count_sprites(c);
	s = -1;
	while (++s < total)
	{
		z = -1;
		while (++z < total)
		{
			if (c->sprites[s].dist < c->sprites[z].dist)
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
	int x;
	int y;
	int s;
printf("search sprites | total: %d\n", count_sprites(c));
	c->sprites = malloc(sizeof(t_sprite) * (count_sprites(c)));
	s = 0;
	x = 0;
	while (c->map[x])
	{
		y = 0;
		while (c->map[x][y])
		{
			if (c->map[x][y] == OBJETO)
			{
				c->sprites[s].x = x + 0.5;
				c->sprites[s].y = y + 0.5;
				c->sprites[s].dist = ((c->mov.posx - c->sprites[s].x) * (c->mov.posx - c->sprites[s].x)
						+ (c->mov.posy - c->sprites[s].y) * (c->mov.posy - c->sprites[s].y));
				printf("sprite %d: (x,y):(%f,%f) dist %d\n", s, c->sprites[s].x, c->sprites[s].y, c->sprites[s].dist);
				s++;
			}
			y++;
		}
		x++;
	}

}

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

	printf("startY %d | endY %d | startX %d | endX %d\n", c->sp.draw_starty, c->sp.draw_endy, c->sp.draw_startx, c->sp.draw_endx);
}

static void sprite_loop(t_cub *c, int width, int screenx, int transfy, int height, double *zbuf)
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
		printf("transfy %d | zbuf %f\n", transfy, zbuf[x]);
		if (transfy >= 0 && x >= 0 && x <= c->win.wid && (double)transfy < (zbuf[x]-0.3))
		{
			printf("hola\n");
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

void sprite2screen(t_cub *c, double *zbuf)
{
	double inv_det;
	double transformx;
	double transformy;
	int sprite_screenx;
	int sp_height;
	int sp_width;
	int s;
	int total;

	total = count_sprites(c);
	s = -1;
	sort_sprite(c);
	while (++s < total)
	{
		c->sp.posx = (double)c->sprites[s].x - c->mov.posx;
		c->sp.posy = (double)c->sprites[s].y - c->mov.posy;

		inv_det = 1.0 / (c->mov.planex * c->mov.diry - c->mov.dirx * c->mov.planey);
		transformx = inv_det * (c->mov.diry * c->sp.posx - c->mov.dirx * c->sp.posy);
		transformy = inv_det * (-c->mov.planey * c->sp.posx + c->mov.planex * c->sp.posy);

		sprite_screenx = (int)((c->win.wid / 2) * (1 + transformx / transformy));
		sp_height = abs((int)(c->win.hei / transformy));
		sp_width = abs((int)(c->win.hei / transformy));
		printf("hei %d | wid %d\n", sp_height, sp_width);
		sp_draw(c, sp_height, sp_width, sprite_screenx);
		sprite_loop(c, sp_width, sprite_screenx, transformy, sp_height, zbuf);
	}
}
