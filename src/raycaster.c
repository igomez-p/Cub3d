#include "../inc/cub.h"

#define AND_ING     8355711
#define FRAME_TIME  1000.0
#define SQUARES_SEC 5.0
#define RADIANS_SEC 3.0

static void dda(t_cub *c)
{
    while (c->ray.hit == 0)
    {
    //jump to next map square, OR in x-direction, OR in y-direction
        if(c->ray.sidex < c->ray.sidey)
        {
            c->ray.sidex += c->ray.deltax;
            c->mov.mapx += c->ray.stepx;
            c->ray.step = 0;
        }
        else
        {
            c->ray.sidey += c->ray.deltay;
            c->mov.mapy += c->ray.stepy;
            c->ray.step = 1;
        }
        //Check if ray has hit a wall
        if(c->map[c->mov.mapx][c->mov.mapy] > 0) c->ray.hit = 1;
    }

}

static void ray_pos_dir(t_cub *c, int x)
{
    c->cam.x = 2 * x / (double)c->res.rend_x - 1;
    c->ray.dirx = c->mov.dirx + c->mov.planex * c->cam.x;
    c->ray.diry = c->mov.diry + c->mov.planey * c->cam.x;

    c->mov.mapx = (int)c->mov.posx;
    c->mov.mapy = (int)c->mov.posy;

    if (c->ray.diry == 0)
        c->ray.deltax = 0.0; // Prescindir si cada vez inicializo vbles
    else
    {
        if (c->ray.dirx == 0)
            c->ray.deltax = 1;
        else
            c->ray.deltax = fabs(1 / c->ray.dirx);
    }

    if (c->ray.dirx == 0)
        c->ray.deltay = 0.0; // Prescindir si cada vez inicializo vbles
    else
    {
        if (c->ray.diry == 0)
            c->ray.deltay = 1;
        else
            c->ray.deltay = fabs(1/c->ray.diry);
    }
}

static void perpRay_distance(t_cub *c)
{
    if (c->ray.side == 0)
        c->ray.perp = (c->mov.mapx - c->mov.posx + (1 - c->ray.stepx) / 2) / c->ray.dirx;
    else
        c->ray.perp = (c->mov.mapy - c->mov.posy + (1 - c->ray.stepy) / 2) / c->ray.diry;
}

static void draw_calculus(t_cub *c)
{
    c->ray.lineh = (int)(c->res.rend_y / c->ray.perp);

    c->draw.start = -c->ray.lineh / 2 + c->res.rend_y / 2;
    if (c->draw.start < 0)
        c->draw.start = 0;

    c->draw.end = c->ray.lineh / 2 + c->res.rend_y / 2;
    if (c->draw.end >= c->res.rend_y)
        c->draw.end = c->res.rend_y - 1;
}

static void texturing_calculus(t_cub *c)
{
    c->no.num = c->map[c->mov.mapx][c->mov.mapy] - 1;
    c->so.num = c->map[c->mov.mapx][c->mov.mapy] - 1;
    c->we.num = c->map[c->mov.mapx][c->mov.mapy] - 1;
    c->ea.num = c->map[c->mov.mapx][c->mov.mapy] - 1;
    c->sp.num = c->map[c->mov.mapx][c->mov.mapy] - 1;
}

static void xcoord_texture(t_cub *c)
{
    c->no.x = (int)(c->draw.wallx * (double)(c->no.wid));
    c->so.x = (int)(c->draw.wallx * (double)(c->so.wid));
    c->we.x = (int)(c->draw.wallx * (double)(c->we.wid));
    c->ea.x = (int)(c->draw.wallx * (double)(c->ea.wid));
    c->sp.x = (int)(c->draw.wallx * (double)(c->sp.wid));

    if ((c->ray.side == 0 && c->ray.dirx > 0) || (c->ray.side == 1 && c->ray.diry < 0))
    {
        c->no.x = c->no.wid - c->no.x - 1;
        c->so.x = c->so.wid - c->so.x - 1;
        c->we.x = c->we.wid - c->we.x - 1;
        c->ea.x = c->ea.wid - c->ea.x - 1;
        c->sp.x = c->sp.wid - c->sp.x - 1;
    }
}

static void wallx_value(t_cub *c)
{
    if (c->ray.side == 0)
        c->draw.wallx = c->mov.posy + c->ray.perp * c->ray.diry;
    else
        c->draw.wallx = c->mov.posx + c->ray.perp * c->ray.dirx;

}

static void draw_textures(t_cub *c, t_img tex, int x)
{
    c->ray.step = 1.0 * tex.hei / c->ray.lineh;
    tex.pos = (c->draw.start - c->res.rend_y / 2 + c->ray.lineh / 2) * c->ray.step;
    for (int y = c->draw.start; y < c->draw.end; y++)
    {
        tex.y = (int)tex.pos & (tex.hei - 1);
        tex.pos += c->ray.step;
        int color = tex.addr[tex.wid * tex.y + tex.x];
        if (c->ray.side == 1)
            color = (color >> 1) & AND_ING;

        c->win.addr[c->win.wid * y + x] = color;
    }
}

int raycaster(t_cub *c)
{
    //double time, old_time;

    while (1)
    {
        for (int x = 0; x < c->res.rend_x; x++)
        {
            ray_pos_dir(c, x);
            step_initialSide(c);
            dda(c);
            perpRay_distance(c);
            draw_calculus(c);
            texturing_calculus(c);
            wallx_value(c);
            xcoord_texture(c);
            draw_textures(c, c->no, x);
            move_keys(c, 2); //, frame_time(time, old_time) * SQUARES_SEC);
            rotate_keys(c, 2); //, frame_time(time, old_time) * RADIANS_SEC);
        }
    }
}
