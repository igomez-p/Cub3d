/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:08:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/29 20:18:45 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	remove_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		*line = *line + 1;
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
		return (0);
	return (1);
}

void	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		clean_exit(NULL, "The file extension must be .cub\n", 1);
}

static void	find_id(t_cub *c)
{
	if (all_textures(c))
		check_open_tex(c);
	if (!empty_line(c->line) && check_identifiers(c) == TOTAL_INFO)
		free_str_exit(c, "No information allowed after the map\n", c->r.stc);
	else if (ft_strchr(c->line, 'R'))
		info_res(c->line, c);
	else if (is_texture(c->line))
		info_tex(c->line, c);
	else if (ft_strchr(c->line, 'F') || ft_strchr(c->line, 'C'))
		info_color(c->line, c);
	else if (ft_strchr(c->line, '1') && check_identifiers(c) == TOTAL_IDS)
	{
		c->r.stc = info_map(c->line, c->r.stc, c);
		c->r.stc = ft_swap(c->r.stc, "\n");
	}
	else if (ft_strchr(c->line, '1') && check_identifiers(c) < TOTAL_IDS)
		free_str_exit(c, "Identifiers missing\n", c->r.stc);
	else if (empty_line(c->line) && c->r.stc != NULL)
	{
		ft_split(&c->r.stc, '\n', c);
		c->check.map = 1;
	}
	else if (!empty_line(c->line))
		free_str_exit(c, "Unrecognized identifier\n", c->r.stc);
}

void	read_cub(char *filename, t_cub *info)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "Cub file could not be opened\n", 1);
	else
	{
		while (get_next_line(fd, &info->line, &info->r.b, &info->r.l) > 0)
		{
			find_id(info);
			free(info->line);
			info->line = 0;
		}
		if (info->line != NULL && ft_strchr(info->line, '1'))
			info->r.stc = info_map(info->line, info->r.stc, info);
		//if (!empty_line(info->line) && check_identifiers(info) > TOTAL_IDS)
		if (check_bad_end(info))
			free_str_exit(info, "No information allowed after the map\n", info->r.stc);
		ft_split(&info->r.stc, '\n', info);
		free(info->r.stc);
		close (fd);
		if (!info->map)
			clean_exit(info, "There is no map\n", 1);
		info->check.map = 1;
	}
}
