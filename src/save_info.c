
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:21:03 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 19:33:39 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static int	save_int(char **line)
{
	char	*num;
	char	caracter[2];
	int		n;

	n = 0;
	num = ft_strdup("");
	while (!ft_isdigit((int)**line) && **line)
		*line = *line + 1;
	while (ft_isdigit((int)**line) && **line)
	{
		caracter[0] = **line;
		caracter[1] = '\0';
		num = ft_swap(num, caracter);
		*line = *line + 1;
	}
	if (check_resolution(num))
		n = ft_atoi(num);
	if (n < 0)
		n = 0;
	free(num);
	return (n);
}

void		info_res(char *line, t_cub *info)
{
	remove_spaces(&line);
	if (!ft_strncmp(line, "R", 1) && !info->check.res)
	{
		if (line[1] != SPACE)
			clean_exit(info, "Wrong screen resolution\n", 1);
		if (error_res_elements(line))
			clean_exit(info, "Characters not allowed in resolution\n", 1);
		info->res.x = save_int(&line);
		info->res.y = save_int(&line);
		if (save_int(&line) != 0)
			clean_exit(info, "Too many elements in resolution\n", 1);
		if (info->res.x <= 0 || info->res.y <= 0)
			clean_exit(info, "Wrong screen resolution\n", 1);
		if (info->res.x < 30 || info->res.y < 30)
			clean_exit(info, "Screen resolution too small\n", 1);
		info->check.res = 1;
	} else if (!ft_strncmp(line, "R", 1) && info->check.res)
		clean_exit(info, "Repeated resolution identifier\n", 1);
}

static void	info_color_sky(char *line, t_cub *info)
{
	if (!ft_strncmp(line, "C", 1) && !info->check.sky)
	{
		if (line[1] != SPACE)
			clean_exit(info, "Wrong ceiling color\n", 1);
		info->col.rgb_s[0] = save_int(&line);
		if (!(info->col.rgb_s[0] >= 0 && info->col.rgb_s[0] <= 255))
			clean_exit(info, "Wrong R ceiling value\n", 1);
		info->col.rgb_s[1] = save_int(&line);
		if (!(info->col.rgb_s[1] >= 0 && info->col.rgb_s[1] <= 255))
			clean_exit(info, "Wrong G ceiling value\n", 1);
		info->col.rgb_s[2] = save_int(&line);
		if (!(info->col.rgb_s[2] >= 0 && info->col.rgb_s[2] <= 255))
			clean_exit(info, "Wrong B ceiling value\n", 1);
		if (save_int(&line) > 0)
			clean_exit(info, "Too many elements in ceiling color\n", 1);
		info->check.sky = 1;
	}
	else if (!ft_strncmp(line, "C", 1) && info->check.sky)
		clean_exit(info, "Repeated ceiling color identifier\n", 1);
}

void		info_color(char *line, t_cub *info)
{
	error_rgb_elements(info, line);
	remove_spaces(&line);
	if (!ft_strncmp(line, "F", 1) && !info->check.floor)
	{
		if (line[1] != SPACE)
			clean_exit(info, "Wrong floor color\n", 1);
		info->col.rgb_f[0] = save_int(&line);
		if (!(info->col.rgb_f[0] >= 0 && info->col.rgb_f[0] <= 255))
			clean_exit(info, "Wrong R floor value\n", 1);
		info->col.rgb_f[1] = save_int(&line);
		if (!(info->col.rgb_f[1] >= 0 && info->col.rgb_f[1] <= 255))
			clean_exit(info, "Wrong G floor value\n", 1);
		info->col.rgb_f[2] = save_int(&line);
		if (!(info->col.rgb_f[2] >= 0 && info->col.rgb_f[2] <= 255))
			clean_exit(info, "Wrong B floor value\n", 1);
		if (save_int(&line) > 0)
			clean_exit(info, "Too many elements in floor color\n", 1);
		info->check.floor = 1;
	}
	else if (!ft_strncmp(line, "F", 1) && info->check.floor)
		clean_exit(info, "Repeated floor color identifier\n", 1);
	
	info_color_sky(line, info);
}

void		refill_map(t_cub *c)
{
	int w;
	char **map;
	int k;

	w = map_dimensions(c);
	map = malloc((c->nrows+1)*sizeof(char *));
	k = -1;
	while (c->map[++k])
	{
		map[k] = malloc((w+1)*sizeof(char));
		int len = ft_strlen(c->map[k]);
		ft_memcpy(map[k], c->map[k], len);
		if (len < w)
			ft_memset(&map[k][len], ' ', w-len);

		map[k][w] = '\0';
	}
	map[k] = NULL;
	free_map(c);
	c->map = map;
}