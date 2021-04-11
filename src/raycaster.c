#include "../inc/cub.h"

#define AND_ING     8355711
#define FRAME_TIME  1000.0
#define SQUARES_SEC 5.0
#define RADIANS_SEC 3.0

static void dda(t_cub *c)
{
    while (c->ray.hit == 0)
    {
        if(c->ray.sidex < c->ray.sidey)
        {
            c->ray.sidex += c->ray.deltax;
            c->mov.mapx += c->ray.stepx;
            c->ray.step = 0 + (c->ray.dirx < 0);
            printf("mapx %d ---- stepx %d\n", c->mov.mapx, c->ray.stepx);
        }
        else
        {
            c->ray.sidey += c->ray.deltay;
            c->mov.mapy += c->ray.stepy;
            c->ray.step = 2 + (c->ray.diry > 0);
            printf("mapy %d ---- stepy %d\n", c->mov.mapy, c->ray.stepy);
        }
        if(c->map[c->mov.mapx][c->mov.mapy] == MURO) c->ray.hit = 1;
        printf("map[%d][%d] %c | hit %d\n", c->mov.mapx, c->mov.mapy, c->map[c->mov.mapx][c->mov.mapy], c->ray.hit);
    }

}

static void ray_pos_dir(t_cub *c, int x)
{
    c->cam.x = 2 * x / (double)c->win.wid - 1;
    c->ray.dirx = c->mov.dirx + c->mov.planex * c->cam.x;
    c->ray.diry = c->mov.diry + c->mov.planey * c->cam.x;

    c->mov.mapx = (int)c->mov.posx;
    c->mov.mapy = (int)c->mov.posy;

    if (c->ray.diry != 0)
    {
        if (c->ray.dirx == 0)
            c->ray.deltax = 1;
        else
            c->ray.deltax = fabs(1 / c->ray.dirx);
    }

    if (c->ray.dirx != 0)
    {
        if (c->ray.diry == 0)
            c->ray.deltay = 1;
        else
            c->ray.deltay = fabs(1/c->ray.diry);
    }
}

static void perpRay_distance(t_cub *c)
{
    if (c->ray.side <= 1)
        c->ray.perp = (c->mov.mapx - c->mov.posx + (1 - c->ray.stepx) / 2) / c->ray.dirx;
    else
        c->ray.perp = (c->mov.mapy - c->mov.posy + (1 - c->ray.stepy) / 2) / c->ray.diry;
}

static void draw_calculus(t_cub *c)
{
    c->ray.lineh = (int)((double)c->win.hei / c->ray.perp);
printf("lineh %d | perp %f\n\r", c->ray.lineh, c->ray.perp);
    c->draw.start = -c->ray.lineh / 2 + c->win.hei / 2;
    if (c->draw.start < 0)
        c->draw.start = 0;

    c->draw.end = c->ray.lineh / 2 + c->win.hei / 2;
    if (c->draw.end >= c->win.hei)
        c->draw.end = c->win.hei - 1;
    if (c->draw.end < 0)
        c->draw.end = 0;
}

/*static void texturing_calculus(t_cub *c)
{
    c->no.num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;
    c->so.num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;
    c->we.num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;
    c->ea.num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;
//    c->sp.num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;

   // c->twall[c->ray.side].num = (c->map[c->mov.mapx][c->mov.mapy] - 48) - 1;
}*/

static void xcoord_texture(t_cub *c)
{
    /*c->no.x = (int)(c->draw.wallx * (double)(c->no.wid));
    c->so.x = (int)(c->draw.wallx * (double)(c->so.wid));
    c->we.x = (int)(c->draw.wallx * (double)(c->we.wid));
    c->ea.x = (int)(c->draw.wallx * (double)(c->ea.wid));*/
    c->ray.x = (int)(c->draw.wallx * (double)(c->twall[c->ray.side].wid));
   // c->sp.x = (int)(c->draw.wallx * (double)(c->sp.wid));

    if ((c->ray.side <= 1 && c->ray.dirx > 0) || (c->ray.side >= 2 && c->ray.diry > 0))
    {
        c->ray.x = c->twall[c->ray.side].wid - c->ray.x - 1;
        /*c->no.x = c->no.wid - c->no.x - 1;
        c->so.x = c->so.wid - c->so.x - 1;
        c->we.x = c->we.wid - c->we.x - 1;
        c->ea.x = c->ea.wid - c->ea.x - 1;
        c->sp.x = c->sp.wid - c->sp.x - 1;*/
    }
}

static void wallx_value(t_cub *c)
{
    if (c->ray.side <= 1)
        c->draw.wallx = c->mov.posy + c->ray.perp * c->ray.diry;
    else
        c->draw.wallx = c->mov.posx + c->ray.perp * c->ray.dirx;

    c->draw.wallx -= (floor)(c->draw.wallx);
}

static void draw_textures(t_cub *c, int x)
{
    c->ray.step = 1.0 * c->twall[c->ray.side].hei / c->ray.lineh;
    c->ray.pos = (c->draw.start - c->win.hei / 2 + c->ray.lineh / 2) * c->ray.step;
    c->ray.y = c->draw.start;
    while (c->ray.y < c->draw.end)
    {
        c->ray.y = (int)c->ray.pos & (c->twall[c->ray.side].hei - 1);
        c->ray.pos += c->ray.step;
        int color = c->twall[c->ray.side].addr[c->twall[c->ray.side].wid * c->ray.y + c->ray.x];
        if (c->ray.side % 2)
            color = (color >> 1) & AND_ING;

        //c->win.addr[c->win.wid * y + x] = color;
        mlx_pixel_put(c->libx.mlx, c->libx.window, x, c->ray.y, 0x22aa77);
        c->ray.y++;
    }
}

int raycaster(t_cub *c, int x)
{    
    init_raycast_vble(c);
    printf("ray1\n");
    ray_pos_dir(c, x);
    printf("ray2\n");
    step_initialSide(c);
    printf("ray3\n");
    dda(c);
    printf("ray4\n");
    perpRay_distance(c);
    printf("ray5\n");
    draw_calculus(c);
    printf("ray6\n");
    //texturing_calculus(c);
    wallx_value(c);
    printf("ray7\n");
    xcoord_texture(c);
    printf("ray8\n");
    draw_textures(c, x);
    printf("ray9\n");
    move_keys(c, 1); //, frame_time(time, old_time) * SQUARES_SEC);
    printf("ray10\n");
    rotate_keys(c, 1); //, frame_time(time, old_time) * RADIANS_SEC);
    printf("ray11\n");

    return 1;
}
