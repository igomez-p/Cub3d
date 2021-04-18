
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
#include "../inc/libft.h"

static char	*path_tex(char *line, t_cub *c)
{
	int i;

	line = ft_strnstr(line, "./", ft_strlen(line));
	if (!line)
	{
		perror("Error\nNo se encuentra la textura\n");
		return (NULL);
	}
	i = ft_strlen(line) - 1;
	while (line[i] == ' ')
	{
		line[i] = '\0';
		i--;
	}
	if (check_repeated_text(c, line))
		return (ft_strdup(line));

	clean_exit(c, "Textura repetida\n", 1);
	return NULL;
}

void		info_tex(char *line, t_cub *info)
{
	if (!ft_strncmp(line, "NO", 2) && !info->check.texno)
	{
		if (line[2] != NADA || !(info->tex.path_no = path_tex(line, info)))
			clean_exit(info, "Textura norte incorrecta\n", 1);
		info->check.texno = 1;
	}
	else if (!ft_strncmp(line, "SO", 2) && !info->check.texso)
	{
		if (line[2] != NADA || !(info->tex.path_so = path_tex(line, info)))
			clean_exit(info, "Textura sur incorrecta\n", 1);
		info->check.texso = 1;
	}
	else if (!ft_strncmp(line, "WE", 2) && !info->check.texwe)
	{
		if (line[2] != NADA || !(info->tex.path_we = path_tex(line, info)))
			clean_exit(info, "Textura oeste incorrecta\n", 1);
		info->check.texwe = 1;
	}
	else if (!ft_strncmp(line, "EA", 2) && !info->check.texea)
	{
		if (line[2] != NADA || !(info->tex.path_ea = path_tex(line, info)))
			clean_exit(info, "Textura este incorrecta\n", 1);
		info->check.texea = 1;
	}
	else if (!ft_strncmp(line, "S", 1) && !info->check.texsp)
	{
		if (line[1] != NADA || !(info->tex.path_sp = path_tex(line, info)))
			clean_exit(info, "Textura sprite incorrecta\n", 1);
		info->check.texsp = 1;
	}
}

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

void	info_res(char *line, t_cub *info)
{
	if (ft_strnstr(line, "R", 1) && !info->check.res)
	{
		if (line[1] != NADA)
			clean_exit(info, "Resolución de pantalla incorrecta\n", 1);
		info->res.rend_x = save_int(&line);
		info->res.rend_y = save_int(&line);
		if (info->res.rend_x <= 0 || info->res.rend_y <= 0)
			clean_exit(info, "Resolución de pantalla incorrecta\n", 1);
		info->check.res = 1;
	}
}

void	info_color(char *line, t_cub *info)
{
	if (ft_strnstr(line, "F", 1) && !info->check.floor)
	{
		if (line[1] != NADA)
			clean_exit(info, "Color de suelo incorrecto\n", 1);
		info->col.rgb_f[0] = save_int(&line);
		if (!(info->col.rgb_f[0] >= 0 && info->col.rgb_f[0] <= 255))
			clean_exit(info, "Valor R suelo incorrecto\n", 1);
		info->col.rgb_f[1] = save_int(&line);
		if (!(info->col.rgb_f[1] >= 0 && info->col.rgb_f[1] <= 255))
			clean_exit(info, "Valor G suelo incorrecto\n", 1);
		info->col.rgb_f[2] = save_int(&line);
		if (!(info->col.rgb_f[2] >= 0 && info->col.rgb_f[2] <= 255))
			clean_exit(info, "Valor B suelo incorrecto\n", 1);
		info->check.floor = 1;
	}
	else if (ft_strnstr(line, "C", 1) && !info->check.sky)
	{
		if (line[1] != NADA)
			clean_exit(info, "Color de techo incorrecto\n", 1);
		info->col.rgb_s[0] = save_int(&line);
		if (!(info->col.rgb_s[0] >= 0 && info->col.rgb_s[0] <= 255))
			clean_exit(info, "Valor R techo incorrecto\n", 1);
		info->col.rgb_s[1] = save_int(&line);
		if (!(info->col.rgb_s[1] >= 0 && info->col.rgb_s[1] <= 255))
			clean_exit(info, "Valor G techo incorrecto\n", 1);
		info->col.rgb_s[2] = save_int(&line);
		if (!(info->col.rgb_s[2] >= 0 && info->col.rgb_s[2] <= 255))
			clean_exit(info, "Valor B techo incorrecto\n", 1);
		info->check.sky = 1;
	}
}
