#include "../inc/cub.h"

void step_initialSide(t_cub *c)
{
  if(c->ray.dirx < 0)
  {
    c->ray.stepx = -1;
    c->ray.sidex = (c->mov.posx - c->mov.mapx) * c->ray.deltax;
  }
  else
  {
    c->ray.stepx = 1;
    c->ray.sidex = (c->mov.mapx + 1.0 - c->mov.posx) * c->ray.deltax;
  }

  if(c->ray.diry < 0)
  {
    c->ray.stepy = -1;
    c->ray.sidey = (c->mov.posy - c->mov.mapy) * c->ray.deltay;
  }
  else
  {
    c->ray.stepy = 1;
    c->ray.sidey = (c->mov.mapy + 1.0 - c->mov.posy) * c->ray.deltay;
  }
}

void move_keys(t_cub *c, double speed)
{
    //move forward if no wall in front of you
    if(c->mov.up)
    {
      if(c->map[(int)(c->mov.posx + c->mov.dirx * speed)][(int)c->mov.posy] == VACIO) c->mov.posx += c->mov.dirx * speed;
      if(c->map[(int)c->mov.posx][(int)(c->mov.posy + c->mov.diry * speed)] == VACIO) c->mov.posy += c->mov.diry * speed;
    }
    //move backwards if no wall behind you
    if(c->mov.down)
    {
      if(c->map[(int)(c->mov.posx - c->mov.dirx * speed)][(int)c->mov.posy] == VACIO) c->mov.posx -= c->mov.dirx * speed;
      if(c->map[(int)c->mov.posx][(int)(c->mov.posy - c->mov.diry * speed)] == VACIO) c->mov.posy -= c->mov.diry * speed;
    }
    //move to the right if no wall next to your right
    if(c->mov.right)
    {
      if(c->map[(int)(c->mov.posx + c->mov.planex * speed)][(int)c->mov.posy] == VACIO) c->mov.posx += c->mov.planex * speed;
      if(c->map[(int)c->mov.posx][(int)(c->mov.posy + c->mov.planey * speed)] == VACIO) c->mov.posy += c->mov.planey * speed;
    }
    //move to the left if no wall next to your left
    if(c->mov.left)
    {
      if(c->map[(int)(c->mov.posx - c->mov.planex * speed)][(int)c->mov.posy] == VACIO) c->mov.posx -= c->mov.planex * speed;
      if(c->map[(int)c->mov.posx][(int)(c->mov.posy - c->mov.planey * speed)] == VACIO) c->mov.posy -= c->mov.planey * speed;
    }
}

void rotate_keys(t_cub *c, double speed)
{
    //rotate to the right
    if(c->cam.right)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = c->mov.dirx;
      c->mov.dirx = c->mov.dirx * cos(-speed) - c->mov.diry * sin(-speed);
      c->mov.dirx = oldDirX * sin(-speed) + c->mov.diry * cos(-speed);
      double oldPlaneX = c->mov.planex;
      c->mov.planex = c->mov.planex * cos(-speed) - c->mov.planey * sin(-speed);
      c->mov.planey = oldPlaneX * sin(-speed) + c->mov.planey * cos(-speed);
    }
    //rotate to the left
    if(c->cam.left)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = c->mov.dirx;
      c->mov.dirx = c->mov.dirx * cos(speed) - c->mov.diry * sin(speed);
      c->mov.diry = oldDirX * sin(speed) + c->mov.diry * cos(speed);
      double oldPlaneX = c->mov.planex;
      c->mov.planex = c->mov.planex * cos(speed) - c->mov.planey * sin(speed);
      c->mov.planey = oldPlaneX * sin(speed) + c->mov.planey * cos(speed);
    }
}
