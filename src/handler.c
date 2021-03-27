/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:19:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/03/27 18:20:06 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

// Tanto para KeyPress como para KeyRelease (^: xor)
int key_handler(int key, t_cub *c)
{
	printf("key %d\n\r", key);
	if (key == (int)KEY_W || key == (int)'w')
		c->player.up ^= 1;
	else if (key == (int)KEY_A || key == (int)'a')
		c->player.left ^= 1;
	else if (key == (int)KEY_S || key == (int)'s')
		c->player.down ^= 1;
	else if (key == (int)KEY_D || key == (int)'d')
		c->player.right ^= 1;
	else if (key == (int)KEY_RIGHT)
		c->cam.right ^= 1;
	else if (key == (int)KEY_LEFT)
		c->cam.left ^= 1;	
	/*else if (key == (int)KEY_SPACE)
		printf("key space %d\n\r", key);
	else if (key == (int)KEY_ESC)
		exit_program(c);
*/
	return 1;
}

int			exit_handler(t_cub *c)
{
	//int			i;

	write(1, "Closing program...\n", 19);
	//i = 0;

//	TODO: LIBERAR MAPA

//	if (t->fd > 0)
//		close(t->fd);
	if (c->libx.img)
		mlx_destroy_image(c->libx.mlx, c->libx.img);
	if (c->libx.window)
		mlx_destroy_window(c->libx.mlx, c->libx.window);

	exit(0);
	return (0);
}