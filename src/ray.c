/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:10:42 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 19:51:09 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"
#include <math.h>

static void rect(int x, int y, int width, int height, t_cub *c, int suelo)
{
    int color = 0x764522;
    if (suelo)  color = 0x0000ff;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			c->win.data[y * width + x] = color; //0x0222ff;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->libx.img, 0, 0);
}

static void line(int x1, int techo, int x2, int suelo, t_cub *c)
{
	c->win.data[x1 * techo + x2 + suelo] = 0xffffff; //0x026600;
	mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->libx.img, 0, 0);
}

int draw(t_cub *c)
{
    float FOV = GRADOS2RADIAN(64);

    //Calculamos el delta time:
 //   c->ray.delta = millis() - c->ray.last_time;

    //Pintar el cielo y el suelo:
  //  fill(30);
    rect(0,0,c->res.rend_x, c->res.rend_y/2, c, 0); //Cielo
  //  fill(120);
    rect(0,c->res.rend_y/2,c->res.rend_x, c->res.rend_y/2, c, 1); //Suelo

    int x = 0;
    while (x < c->res.rend_x)
    {
        //La posición inicial del rayo será la del jugador:
        float xRayo = c->player.x;
        float yRayo = c->player.y;

        //Calculamos su ángulo inicial:
        float aRayo = (c->player.angle - FOV / 2.0) + x*(FOV / c->res.rend_x);

        //Calculamos el incremento:
        float xIncremento = cos(aRayo)*PASO;
        float yIncremento = sin(aRayo)*PASO;

        //Calcular la trayectoria del rayo, paso a paso:
        int choque = 0;
        while(!choque)
        {
            //Calcular un nuevo punto de la trayectoria:
            xRayo += xIncremento;
            yRayo += yIncremento;

            //Si el rayo sale del mapa, o si colisiona con un muro, salimos del bucle while:
            if( xRayo < 0 || c->map[(int)yRayo][(int)xRayo] || yRayo < 0 || c->map[(int)yRayo] || c->map[(int)yRayo][(int)xRayo] != VACIO)
            {
                choque = 1;
            }
        }

        //Calcular la distancia corregida del jugador al punto de colisión:
        float distancia = sqrt(pow(xRayo - c->player.x, 2) + pow(yRayo - c->player.y, 2));
        distancia = distancia * cos(aRayo - c->player.angle);

        //Calcular la altura del muro:
        float altura = 32;//min(c->res.rend_y, c->res.rend_x / distancia);

        //Calcular el píxel de la pantalla donde hay que empezar a dibujar el muro (nTecho) y donde hay que acabar (nSuelo)
        int nTecho = (int)((float)c->res.rend_y / 2.0 - altura/2);
        int nSuelo = (int)((float)c->res.rend_y / 2.0 + altura/2);

        //Dibujar la línea vertical:
        line(x, nTecho, x, nSuelo, c);

        //Comprobar si hay que dibujar un borde lateral:
        if(fabsf(altura - c->ray.alt_ant) >= 10)
        {
            if(altura > c->ray.alt_ant)
                line(x, nTecho, x, nSuelo, c);
            else
                line(x-1, c->ray.ntecho_ant, x-1, c->ray.nsuelo_ant, c);
        }

        //Guardar los parámetros de la columna actual:
        c->ray.alt_ant = altura;
        c->ray.ntecho_ant = nTecho;
        c->ray.nsuelo_ant = nSuelo;

        // DRAW bordes

        x++;
    }
	return (1);
}
