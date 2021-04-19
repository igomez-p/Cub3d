
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
	while (**line && **line == NADA)
		*line = *line + 1;

}

void check_extension(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		clean_exit(NULL, "Extensión de archivo debe ser .cub\n", 1);
}

// Función para leer archivo .cub
void	read_cub(char *filename, t_cub *info)
{
	int	fd;
	char	*linea;
	char	*stc_line;

	stc_line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		clean_exit(info, "Fallo al abrir el archivo\n", 1);
	else
	{
		linea = 0;
		while (get_next_line(fd, &linea) > 0)
		{
			if (ft_strchr(linea, 'R'))
				info_res(linea, info);
			else if (is_texture(linea))
				info_tex(linea, info);
			else if (ft_strchr(linea, 'F') || ft_strchr(linea, 'C'))
				info_color(linea, info);
			else if (ft_strchr(linea, '1') && check_identifiers(info) == TOTAL_IDS)
			{
				stc_line = info_map(linea, stc_line, info);
				stc_line = ft_swap(stc_line, "\n");
			}
			else if (ft_strchr(linea, '1') && check_identifiers(info) < TOTAL_IDS)
				clean_exit(info, "Faltan identificadores\n", 1);
			else if (!empty_line(linea))
				clean_exit(info, "Identificador no reconocido\n", 1);

			free(linea);
			linea = 0;
		}
		if (linea != NULL && ft_strchr(linea, '1'))
			stc_line = info_map(linea, stc_line, info);

		if (linea != NULL && check_identifiers(info) == TOTAL_INFO)
			clean_exit(info, "El mapa debe ir al final del fichero\n", 1);

		info->map = ft_split(stc_line, '\n');
		info->check.map = 1;
		free(stc_line); // SOLUCIONADO LOS MEMORY LEAKS ??
		close (fd);
	}
}
