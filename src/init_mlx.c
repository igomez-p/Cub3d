/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:18:11 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/17 21:20:43 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void init_sp_vble(t_cub *c)
{
    c->sp.img = NULL;
    c->sp.addr = NULL;
    c->sp.wid = 0;
    c->sp.hei = 0;
    c->sp.bpp = 0;
    c->sp.sz = 0;
    c->sp.endian = 0;
    c->sp.posx = 0.0;
    c->sp.posy = 0.0;
    c->sp.draw_startx = 0;
    c->sp.draw_starty = 0;
    c->sp.draw_endx = 0;
    c->sp.draw_endy = 0;
}

void init_tex_vble(t_cub *c)
{
    int x;

    x = 0;
    while (x < MAX_TEXTURES)
    {
        c->twall[x].img = NULL;
        c->twall[x].addr = NULL;
        c->twall[x].wid = 0;
        c->twall[x].hei = 0;
        c->twall[x].bpp = 0;
        c->twall[x].sz = 0;
        c->twall[x].endian = 0;
        x++;
    }
    init_sp_vble(c);
}

static void xpm2image(t_cub *c)
{
    int x;

    c->twall[NO].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_no, &c->twall[NO].wid, &c->twall[NO].hei);
    c->twall[SO].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_so, &c->twall[SO].wid, &c->twall[SO].hei);
    c->twall[EA].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_ea, &c->twall[EA].wid, &c->twall[EA].hei);
    c->twall[WE].img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_we, &c->twall[WE].wid, &c->twall[WE].hei);
    c->sp.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_sp, &c->sp.wid, &c->sp.hei);

    x = 0;
    while (x < MAX_TEXTURES)
    {
        if (!c->twall[x].img)
            clean_exit(c, "Error al convertir textura de un muro\n", 1);
        else
            c->twall[x].addr = (int *)mlx_get_data_addr(c->twall[x].img, &c->twall[x].bpp, &c->twall[x].sz, &c->twall[x].endian);

        x++;
    }
    if (!c->sp.img)
        clean_exit(c, "Error al convertir textura del sprite\n", 1);
    else
        c->sp.addr = (int *)mlx_get_data_addr(c->sp.img, &c->sp.bpp, &c->sp.sz, &c->sp.endian);
}

static void resize_window(t_cub *c, int bmp)
{
    if (c->res.rend_x > c->win.wid && bmp)
        c->win.wid = c->res.rend_x;
    else if (c->res.rend_x <= c->win.wid)
        c->win.wid = c->res.rend_x;

    if (c->res.rend_y > c->win.hei && bmp)
        c->win.hei = c->res.rend_y;
    else if (c->res.rend_y <= c->win.hei)
        c->win.hei = c->res.rend_y;
}

void    init_mlx_func(t_cub *c)
{
    if (!(c->libx.mlx = mlx_init()))
		clean_exit(c, "Error al inicializar MLX\n", 1);
    mlx_get_screen_size(c->libx.mlx, &c->win.wid, &c->win.hei);
    resize_window(c, c->bmp);
	if(!(c->libx.window = mlx_new_window(c->libx.mlx, c->win.wid, c->win.hei, "Cub3D")))
		clean_exit(c, "Error new window\n", 1);
	if (!(c->win.img = mlx_new_image(c->libx.mlx, c->win.wid, c->win.hei)))
		clean_exit(c, "Error new image\n", 1);
	c->win.addr = (int *)mlx_get_data_addr(c->win.img, &c->win.bpp, &c->win.sz, &c->win.endian);

    xpm2image(c);

    mlx_do_key_autorepeatoff(c->libx.mlx);
}
