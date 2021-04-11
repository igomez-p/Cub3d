#include "../inc/cub.h"

static void init_tex_vble(t_cub *c)
{
    c->no.img = NULL;
    c->no.addr = NULL;
    c->no.wid = 0;
    c->no.hei = 0;
    c->no.bpp = 0;
    c->no.sz = 0;
    c->no.endian = 0;
    c->so.img = NULL;
    c->so.addr = NULL;
    c->so.wid = 0;
    c->so.hei = 0;
    c->so.bpp = 0;
    c->so.sz = 0;
    c->so.endian = 0;
    c->sp.img = NULL;
    c->sp.addr = NULL;
    c->sp.wid = 0;
    c->sp.hei = 0;
    c->sp.bpp = 0;
    c->sp.sz = 0;
    c->sp.endian = 0;
}

static void init_tex_vble2(t_cub *c)
{
    c->ea.img = NULL;
    c->ea.addr = NULL;
    c->ea.wid = 0;
    c->ea.hei = 0;
    c->ea.bpp = 0;
    c->ea.sz = 0;
    c->ea.endian = 0;
    c->we.img = NULL;
    c->we.addr = NULL;
    c->we.wid = 0;
    c->we.hei = 0;
    c->we.bpp = 0;
    c->we.sz = 0;
    c->we.endian = 0;
}

static void xpm2image(t_cub *c)
{
    c->no.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_no, &c->no.wid, &c->no.hei);
    c->so.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_so, &c->so.wid, &c->so.hei);
    c->ea.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_ea, &c->ea.wid, &c->ea.hei);
    c->we.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_we, &c->we.wid, &c->we.hei);
    c->sp.img = mlx_xpm_file_to_image(c->libx.mlx, c->tex.path_sp, &c->sp.wid, &c->sp.hei);
}

static void get_textures_addr(t_cub *c)
{
    c->no.addr = (int *)mlx_get_data_addr(c->no.img, &c->no.bpp, &c->no.sz, &c->no.endian);
    c->so.addr = (int *)mlx_get_data_addr(c->so.img, &c->so.bpp, &c->so.sz, &c->so.endian);
    c->ea.addr = (int *)mlx_get_data_addr(c->ea.img, &c->ea.bpp, &c->ea.sz, &c->ea.endian);
    c->we.addr = (int *)mlx_get_data_addr(c->we.img, &c->we.bpp, &c->we.sz, &c->we.endian);
    c->sp.addr = (int *)mlx_get_data_addr(c->sp.img, &c->sp.bpp, &c->sp.sz, &c->sp.endian);
}

static void resize_window(t_cub *c)
{
    if (c->res.rend_x <= c->win.wid)
        c->win.wid = c->res.rend_x;

    if (c->res.rend_y <= c->win.hei)
        c->win.hei = c->res.rend_y;
}

void    init_mlx_func(t_cub *c)
{
    if (!(c->libx.mlx = mlx_init()))
		clean_exit(c, "Error al inicializar MLX\n", 1);
    mlx_get_screen_size(c->libx.mlx, &c->win.wid, &c->win.hei);
    resize_window(c);
	if(!(c->libx.window = mlx_new_window(c->libx.mlx, c->win.wid, c->win.hei, "Cub3D")))
		clean_exit(c, "Error new window\n", 1);
	if (!(c->win.img = mlx_new_image(c->libx.mlx, c->win.wid, c->win.hei)))
		clean_exit(c, "Error new image\n", 1);
	c->win.addr = (int *)mlx_get_data_addr(c->win.img, &c->win.bpp, &c->win.sz, &c->win.endian);

    init_tex_vble(c);
    init_tex_vble2(c);
    xpm2image(c);
    get_textures_addr(c);

    mlx_do_key_autorepeatoff(c->libx.mlx);
}