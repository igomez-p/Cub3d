#include "../inc/cub.h"

#define NO  0
#define SO  1
#define EA  2
#define WE  3

static void init_tex_vble(t_cub *c)
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
    c->sp.img = NULL;
    c->sp.addr = NULL;
    c->sp.wid = 0;
    c->sp.hei = 0;
    c->sp.bpp = 0;
    c->sp.sz = 0;
    c->sp.endian = 0;
}

// TODO: init_tex_sprite(t_cub *c)

/*static void init_tex_vble(t_cub *c)
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
}*/

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
            clean_exit(c, "Error al convertir textura\n", 1);
        
        x++;
    }
}

static void get_textures_addr(t_cub *c)
{
    int x;

    x = 0;
    while (x < MAX_TEXTURES)
    {
        c->twall[x].addr = (int *)mlx_get_data_addr(c->twall[x].img, &c->twall[x].bpp, &c->twall[x].sz, &c->twall[x].endian);
        x++;
    }
    
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
    xpm2image(c);
    get_textures_addr(c);

    mlx_do_key_autorepeatoff(c->libx.mlx);
}