/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:20:38 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 18:48:03 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void move_player(t_cub *c, double speed, int sg, int plane)
{
  double dx;
  double dy;

  dx = c->mov.dirx;
  dy = c->mov.diry;
  if (plane == 1)
  {
    dx = c->mov.planex;
    dy = c->mov.planey;
  }
  if(c->map[(int)(c->mov.posx + sg * dx * speed)][(int)c->mov.posy] == VACIO)
    c->mov.posx += sg * dx * speed;
  if(c->map[(int)c->mov.posx][(int)(c->mov.posy + sg * dy * speed)] == VACIO)
    c->mov.posy += sg * dy * speed;
}

int move_keys(t_cub *c, double speed)
{
  if(c->mov.up)
    move_player(c, speed, 1, 0);
  if(c->mov.down)
    move_player(c, speed, -1, 0);
  if(c->mov.right)
    move_player(c, speed, 1, 1);
  if(c->mov.left)
    move_player(c, speed, -1, 1);

  return (c->mov.up || c->mov.down || c->mov.left || c->mov.right);
}

static void rotate_cam(t_cub *c, double speed)
{
  double oldDirX = c->mov.dirx;
  c->mov.dirx = c->mov.dirx * cos(speed) - c->mov.diry * sin(speed);
  c->mov.diry = oldDirX * sin(speed) + c->mov.diry * cos(speed);
  double oldPlaneX = c->mov.planex;
  c->mov.planex = c->mov.planex * cos(speed) - c->mov.planey * sin(speed);
  c->mov.planey = oldPlaneX * sin(speed) + c->mov.planey * cos(speed);
}

int rotate_keys(t_cub *c, double speed)
{
    if(c->cam.right)
      rotate_cam(c, -speed);
    if(c->cam.left)
      rotate_cam(c, speed);
    return (c->cam.right || c->cam.left);
}
