/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:08:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/25 19:33:36 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	remove_spaces(char **line)
{
	while (**line && **line == SPACE)
		*line = *line + 1;
}

static int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == SPACE)
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
	if (!empty_line(c->line) && check_identifiers(c) == TOTAL_INFO)
		clean_exit(c, "No information allowed after the map\n", 1);
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
		clean_exit(c, "Identifiers missing\n", 1);
	else if (empty_line(c->line) && *stc != NULL)
	{
		ft_split(*stc, '\n', c);
		c->check.map = 1;
	}
	else if (!empty_line(c->line))
		clean_exit(c, "Unrecognized identifier\n", 1);
}

void	read_cub(char *filename, t_cub *info)
{
	int			fd;
	static char	*stc_line = NULL;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "File could not be opened\n", 1);
	else
	{
		info->line = 0;
		while (get_next_line(fd, &info->line) > 0)
		{
			find_id(info, &stc_line);
			free(info->line);
			info->line = 0;
		}
		if (info->line != NULL && ft_strchr(info->line, '1'))
			stc_line = info_map(info->line, stc_line, info);
		if (!empty_line(info->line) && check_identifiers(info) == TOTAL_INFO)
			clean_exit(info, "No information allowed after the map\n", 1);
		ft_split(stc_line, '\n', info);
		info->check.map = 1;
		free(stc_line);
		close (fd);
	}
}
