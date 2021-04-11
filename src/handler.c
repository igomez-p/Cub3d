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

int key_handler(int key, t_cub *c)
{
	printf("key %d\n\r", key);
	if (key == (int)KEY_W_)
		c->mov.up ^= 1;
	else if (key == (int)KEY_A_)
		c->mov.left ^= 1;
	else if (key == (int)KEY_S_)
		c->mov.down ^= 1;
	else if (key == (int)KEY_D_)
		c->mov.right ^= 1;
	else if (key == (int)KEY_RIGHT_)
		c->cam.right ^= 1;
	else if (key == (int)KEY_LEFT_)
		c->cam.left ^= 1;	
	else if (key == (int)KEY_SPACE_)
		printf("key space %d\n\r", key);
	else if (key == (int)KEY_ESC_)
		exit_handler(c);

    return 1;
}

int	exit_handler(t_cub *c)
{
	clean_exit(c, "Closing program...\n", 0);
    return (0);
}

static void	free_map_textures(t_cub *c)
{	
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

	printf("a1\n");
	free_map(c);
}

static void destroy_textures(t_cub *c)
{
	if (c->no.img)
		mlx_destroy_image(c->libx.mlx, c->no.img);
	if (c->so.img)
		mlx_destroy_image(c->libx.mlx, c->so.img);
	if (c->we.img)
		mlx_destroy_image(c->libx.mlx, c->we.img);
	if (c->ea.img)
		mlx_destroy_image(c->libx.mlx, c->ea.img);
	if (c->sp.img)
		mlx_destroy_image(c->libx.mlx, c->sp.img);
}

void	clean_exit(t_cub *c, char *str, int error)
{
	int		len;

	len = ft_strlen(str);
	if (error)
		write(1, "Error\n", 6);
	if (!str)
		perror("");
	else
		write(1, str, len);
printf("a\n");
	free_map_textures(c);
printf("b\n");
	if (c->libx.window)
		mlx_destroy_window(c->libx.mlx, c->libx.window);
	if (c->win.img)
		mlx_destroy_image(c->libx.mlx, c->win.img);
printf("c\n");
	destroy_textures(c);
		printf("d\n");
	exit(1);
}