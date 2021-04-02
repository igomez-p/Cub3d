#include "../inc/cub.h"

void move_keys(t_cub *c, int speed)
{
    //move forward if no wall in front of you
    if(c->mov.up)
    {
      if(c->map[int(c->mov.x + c->mov.dirx * speed)][int(c->mov.y)] == false) c->mov.x += c->mov.dirx * speed;
      if(c->map[int(c->mov.x)][int(c->mov.y + c->mov.diry * speed)] == false) c->mov.y += c->mov.diry * speed;
    }
    //move backwards if no wall behind you
    if(c->mov.down)
    {
      if(c->map[int(c->mov.x - c->mov.dirx * speed)][int(c->mov.y)] == false) c->mov.x -= c->mov.dirx * speed;
      if(c->map[int(c->mov.x)][int(c->mov.y - c->mov.diry * speed)] == false) c->mov.y -= c->mov.diry * speed;
    }
}

int rotate_keys(t_cub *c, int speed)
{
    //rotate to the right
    if(keyDown(c->cam.right))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = c->mov.dirx;
      c->mov.dirx = c->mov.dirx * cos(-speed) - c->mov.diry * sin(-speed);
      c->mov.dirx = oldDirX * sin(-speed) + c->mov.diry * cos(-speed);
      double oldPlaneX = planex;
      planex = planex * cos(-speed) - planey * sin(-speed);
      planey = oldPlaneX * sin(-speed) + planey * cos(-speed);
    }
    //rotate to the left
    if(keyDown(c->cam.left))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirx;
      dirx = dirx * cos(speed) - diry * sin(speed);
      diry = oldDirX * sin(speed) + diry * cos(speed);
      double oldPlaneX = planex;
      planex = planex * cos(speed) - planey * sin(speed);
      planey = oldPlaneX * sin(speed) + planey * cos(speed);
    }
}