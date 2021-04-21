
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:08:54 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/18 19:08:55 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


void remove_spaces(char **line)
{
	while (**line && **line == SPACE)
		*line = *line + 1;
}

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == SPACE)
		i++;

	if (line[i])
		return (0);
	return (1);
}

void check_extension(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		clean_exit(NULL, "The file extension must be .cub\n", 1);
}

void	read_cub(char *filename, t_cub *info)
{
	int	fd;
	char	*line;
	char	*stc_line;

	stc_line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		clean_exit(info, "File could not be opened\n", 1);
	else
	{
		line = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (!empty_line(line) && check_identifiers(info) == TOTAL_INFO)
				clean_exit(info, "No information allowed after the map\n", 1);
			else if (ft_strchr(line, 'R'))
				info_res(line, info);
			else if (is_texture(line))
				info_tex(line, info);
			else if (ft_strchr(line, 'F') || ft_strchr(line, 'C'))
				info_color(line, info);
			else if (ft_strchr(line, '1') && check_identifiers(info) == TOTAL_IDS)
			{
				stc_line = info_map(line, stc_line, info);
				stc_line = ft_swap(stc_line, "\n");
			}
			else if (ft_strchr(line, '1') && check_identifiers(info) < TOTAL_IDS)
				clean_exit(info, "Identifiers missing\n", 1);
			else if (empty_line(line) && stc_line != NULL)
			{
				info->map = ft_split(stc_line, '\n');
				info->check.map = 1;
			}
			else if (!empty_line(line))
				clean_exit(info, "Unrecognized identifier\n", 1);

			free(line);
			line = 0;
		}
		if (line != NULL && ft_strchr(line, '1'))
			stc_line = info_map(line, stc_line, info);

		if (!empty_line(line) && check_identifiers(info) == TOTAL_INFO)
			clean_exit(info, "No information allowed after the map\n", 1);

		info->map = ft_split(stc_line, '\n');
		info->check.map = 1;
		free(stc_line); // SOLUCIONADO LOS MEMORY LEAKS ??
		close (fd);
	}
}
