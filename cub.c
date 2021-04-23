/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/23 20:21:24 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub.h"

int	count_sprites(t_cub *c)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	x = 0;
	while (c->map[x])
	{
		y = 0;
		while (c->map[x][y])
		{
			if (c->map[x][y] == OBJECT)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

int	main(int argc, char *argv[])
{
	t_cub	cub;

	init_struct(&cub);
	if (argc < 2)
	{
		clean_exit(&cub, "Numero de argumentos invalido\n", 1);
		return (-1);
	}
	check_extension(argv[1]);
	read_cub(argv[1], &cub);
	refill_map(&cub);
	check_map_wall(&cub);
	search_player(&cub);
	search_sprites(&cub);
	if (argc == 3 && (!ft_strncmp(argv[2], "--save", 7)))
		save_bmp(&cub);
	init_mlx_func(&cub);
	mlx_hook(cub.libx.window, 2, 1, key_press_handler, &cub);
	mlx_hook(cub.libx.window, 3, 2, key_release_handler, &cub);
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, &cub);
	mlx_loop_hook(cub.libx.mlx, draw, &cub);
	mlx_loop(cub.libx.mlx);
	return (0);
}
