/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:19:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/22 22:17:31 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int			key_press_handler(int key, t_cub *c)
{
	if (key == (int)KEY_W)
		c->mov.up = 1;
	else if (key == (int)KEY_A)
		c->mov.left = 1;
	else if (key == (int)KEY_S)
		c->mov.down = 1;
	else if (key == (int)KEY_D)
		c->mov.right = 1;
	else if (key == (int)KEY_RIGHT)
		c->cam.right = 1;
	else if (key == (int)KEY_LEFT)
		c->cam.left = 1;
	else if (key == (int)KEY_ESCAPE)
		exit_handler(c);

    return (1);
}

int			key_release_handler(int key, t_cub *c)
{
	if (key == (int)KEY_W)
		c->mov.up = 0;
	else if (key == (int)KEY_A)
		c->mov.left = 0;
	else if (key == (int)KEY_S)
		c->mov.down = 0;
	else if (key == (int)KEY_D)
		c->mov.right = 0;
	else if (key == (int)KEY_RIGHT)
		c->cam.right = 0;
	else if (key == (int)KEY_LEFT)
		c->cam.left = 0;
	else if (key == (int)KEY_ESCAPE)
		exit_handler(c);

    return (1);
}

int			exit_handler(t_cub *c)
{
	clean_exit(c, "Closing program...\n", 0);
	return (0);
}

static void	destroy_textures(t_cub *c)
{
	if (c->twall[NO].img)
		mlx_destroy_image(c->libx.mlx, c->twall[NO].img);
	if (c->twall[SO].img)
		mlx_destroy_image(c->libx.mlx, c->twall[SO].img);
	if (c->twall[WE].img)
		mlx_destroy_image(c->libx.mlx, c->twall[WE].img);
	if (c->twall[EA].img)
		mlx_destroy_image(c->libx.mlx, c->twall[EA].img);
	if (c->sp.img)
		mlx_destroy_image(c->libx.mlx, c->sp.img);

	if (c->tex.path_no)
		free(c->tex.path_no);
	if (c->tex.path_so)
		free(c->tex.path_so);
	if (c->tex.path_ea)
		free(c->tex.path_ea);
	if (c->tex.path_we)
		free(c->tex.path_we);
	if (c->tex.path_sp)
		free(c->tex.path_sp);

	free_map(c);
}

void		clean_exit(t_cub *c, char *str, int error)
{
	int	len;

	len = ft_strlen(str);
	if (error)
		write(1, "Error\n", 6);
	if (!str)
		perror("");
	else
		write(1, str, len);

	if (c != NULL)
	{
		if (c->libx.window)
			mlx_destroy_window(c->libx.mlx, c->libx.window);
		if (c->win.img)
			mlx_destroy_image(c->libx.mlx, c->win.img);

		destroy_textures(c);
		if (c->line != NULL)
			free(c->line);
	}
	//system("leaks cub3d");
	exit(1);
}
