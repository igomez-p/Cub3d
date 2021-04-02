#include "../inc/cub.h"

void move_keys(t_cub *c, int speed)
{
    //move forward if no wall in front of you
    if(c->player.up)
    {
      if(worldMap[int(c->player.x + c->player.dirx * speed)][int(c->player.y)] == false) c->player.x += c->player.dirx * speed;
      if(worldMap[int(c->player.x)][int(c->player.y + c->player.diry * speed)] == false) c->player.y += c->player.diry * speed;
    }
    //move backwards if no wall behind you
    if(c->player.down)
    {
      if(worldMap[int(c->player.x - c->player.dirx * speed)][int(c->player.y)] == false) c->player.x -= c->player.dirx * speed;
      if(worldMap[int(c->player.x)][int(c->player.y - c->player.diry * speed)] == false) c->player.y -= c->player.diry * speed;
    }
}

int rotate_keys(t_cub *c, int speed)
{
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = c->player.dirx;
      c->player.dirx = c->player.dirx * cos(-speed) - c->player.diry * sin(-speed);
      c->player.dirx = oldDirX * sin(-speed) + c->player.diry * cos(-speed);
      double oldPlaneX = planex;
      planex = planex * cos(-speed) - planey * sin(-speed);
      planey = oldPlaneX * sin(-speed) + planey * cos(-speed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
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