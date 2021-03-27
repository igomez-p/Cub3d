/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:28:41 by igomez-p          #+#    #+#             */
/*   Updated: 2021/01/31 19:38:03 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void		set_mini_map(t_cub *c)
{
	int	ratio_x;
	int ratio_y;
	int diff;

	ratio_x = c->res.rend_x / (ft_strlen(c->map[0]));
	ratio_y = c->res.rend_y / c->nrows;
	diff = ratio_x - ratio_y;
	c->resz_map = ratio_y + (diff / 2);
	c->resz_map += (c->resz_map % 2) ? 1 : 0;
	c->resz_player = c->resz_map * 0.3;
	c->resz_player = c->resz_player < 10 ? 10 : c->resz_player;
	/*t->life = c->res.rend_x / 5;
	t->life_full = t->life;
	t->reduce = c->res.rend_y / 4;*/
}

static void	print_rect(t_cub *c, int *aux, int color)
{
	int	h;
	int	w;
	//int	*p;
	//int	l;

	//p = c->win.data;
	h = aux[2];
	//l = c->res.rend_x * (int)(c->res.rend_y / 1.2) + (int)(c->res.rend_x / 1.4);
	while (h < aux[3])
	{
		w = aux[0];
		while (w < aux[1])
		{
			//p[l + h * c->res.rend_x + w] = color;
			c->win.data[h * c->res.rend_x + w] = color;
			w++;
		}
		h++;
	}
}

static void	render_player(t_cub *c)
{
	int aux[4];

	aux[0] = c->player.x * 0.15 * c->resz_map;
	aux[2] = c->player.y * 0.15 * c->resz_map;
	aux[3] = aux[2] + c->resz_player * 0.5;
	aux[1] = aux[0] + c->resz_player * 0.5;
	print_rect(c, aux, 65280);
}

int		render_map(t_cub *c)
{
	int			row;
	int			col;
	int			aux[4];

	row = 0;
	while (c->map[row])
	{
		col = 0;
		while (c->map[row][col])
		{
			aux[0] = col * c->resz_map * 0.15;
			aux[2] = row * c->resz_map * 0.15;
			aux[1] = aux[2] + c->resz_map * 0.2;
			aux[3] = aux[0] + c->resz_map * 0.2;
			if (c->map[row][col] == MURO)
				print_rect(c, aux, 125);
			else if (c->map[row][col] == OBJETO)
				print_rect(c, aux, 16711680);
			else if (c->map[row][col] == '3')
				print_rect(c, aux, 1024);
			else
				print_rect(c, aux, 0x00FFFFFF);
			col++;
		}
		row++;
	}
	render_player(c);
	mlx_put_image_to_window(c->libx.mlx, c->libx.window, c->libx.img, 0, 0);
	return (1);
}
