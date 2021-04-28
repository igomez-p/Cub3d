/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 20:37:03 by igomez-p         ###   ########.fr       */
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

static void	check_argc(t_cub *cub, int n, char *str)
{
	if (n < 2 || n > 3)
		clean_exit(cub, "Invalid number of arguments\n", 1);
	if (n == 3 && !ft_strncmp(str, "--save", 6) && str[6] <= SPACE)
		cub->bmp = 1;
	else if (n == 3)
		clean_exit(cub, "Invalid save argument\n", 1);
}

int	main(int argc, char *argv[])
{
	t_cub	cub;

	init_struct(&cub);
	check_argc(&cub, argc, argv[2]);
	check_extension(argv[1]);
	//cub.libx.mlx = mlx_init();
	//if (!cub.libx.mlx)
	//	clean_exit(&cub, "MLX was not initialized\n", 1);
	read_cub(argv[1], &cub);
	refill_map(&cub);
	check_map_wall(&cub);
	search_player(&cub);
	search_sprites(&cub);
	if (cub.bmp)
		save_bmp(&cub);
	init_mlx_func(&cub);
	mlx_hook(cub.libx.window, 2, 1, key_press_handler, &cub);
	mlx_hook(cub.libx.window, 3, 2, key_release_handler, &cub);
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, &cub);
	mlx_loop_hook(cub.libx.mlx, draw, &cub);
	mlx_loop(cub.libx.mlx);
	return (0);
}
