/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:08:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/29 19:33:24 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	remove_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		*line = *line + 1;
}

static int	empty_line(char *line)
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

void	find_id(t_cub *c, char **stc)
{
	if (all_textures(c))
		check_open_tex(c);
	if (!empty_line(c->line) && check_identifiers(c) == TOTAL_INFO)
		free_str_exit(c, "No information allowed after the map\n", *stc);
	else if (ft_strchr(c->line, 'R'))
		info_res(c->line, c);
	else if (is_texture(c->line))
		info_tex(c->line, c);
	else if (ft_strchr(c->line, 'F') || ft_strchr(c->line, 'C'))
		info_color(c->line, c);
	else if (ft_strchr(c->line, '1') && check_identifiers(c) == TOTAL_IDS)
	{
		*stc = info_map(c->line, *stc, c);
		*stc = ft_swap(*stc, "\n");
	}
	else if (ft_strchr(c->line, '1') && check_identifiers(c) < TOTAL_IDS)
		free_str_exit(c, "Identifiers missing\n", *stc);
	else if (empty_line(c->line) && *stc != NULL)
	{
		ft_split(*stc, '\n', c);
		//c->check.map = 1;
	}
	else if (!empty_line(c->line))
		free_str_exit(c, "Unrecognized identifier\n", *stc);
}

void	read_cub(char *filename, t_cub *info)
{
	int			fd;
	static char	*stc_line = NULL;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "Cub file could not be opened\n", 1);
	else
	{
		while (get_next_line(fd, &info->line, &info->r.b, &info->r.l) > 0)
		{
			find_id(info, &stc_line);
			free(info->line);
			info->line = 0;
		}
		if (info->line != NULL && ft_strchr(info->line, '1'))
			stc_line = info_map(info->line, stc_line, info);
		if (!empty_line(info->line) && check_identifiers(info) > TOTAL_IDS)
			free_str_exit(info, "No information allowed after the map\n", stc_line);
		ft_split(stc_line, '\n', info);
		free(stc_line);
		close (fd);
		if (!info->map)
			clean_exit(info, "There is no map\n", 1);
		info->check.map = 1;
	}
}
