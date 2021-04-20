#include "../inc/cub.h"

static char	*path_tex(char *line, t_cub *c, int nchar)
{
	int i;

	i = nchar;
	while (line[i] == NADA)
		i++;
	line = line + i;
	i = ft_strlen(line) - 1;
	while (line[i] == NADA)
	{
		line[i] = '\0';
		i--;
	}
	if (error_tex_elements(line))
		clean_exit(c, "Demasiados elementos en textura\n", 1);

	if (check_text(c, line) == 1)
		return (ft_strdup(line));
	
	if (check_text(c, line) < 0)
		clean_exit(c, "La extensión de textura debe ser .xpm\n", 1);

	clean_exit(c, "Textura repetida\n", 1);
	return NULL;
}


static int vertical_text(char *line, t_cub *info)
{
    if (!ft_strncmp(line, "NO", 2) && !info->check.texno)
	{
		if (line[2] != NADA || !(info->tex.path_no = path_tex(line, info, 2)))
			clean_exit(info, "Textura norte incorrecta\n", 1);
		info->check.texno = 1;
        return (1);
	}
    else if (!ft_strncmp(line, "NO", 2) && info->check.texno)
        clean_exit(info, "Identificador de textura norte duplicado\n", 1);
	else if (!ft_strncmp(line, "SO", 2) && !info->check.texso)
	{
		if (line[2] != NADA || !(info->tex.path_so = path_tex(line, info, 2)))
			clean_exit(info, "Textura sur incorrecta\n", 1);
		info->check.texso = 1;
        return (1);
	}
    else if (!ft_strncmp(line, "SO", 2) && info->check.texso)
        clean_exit(info, "Identificador de textura sur duplicado\n", 1);
    
    return (0);
}

static int horizontal_text(char *line, t_cub *info)
{
    if (!ft_strncmp(line, "WE", 2) && !info->check.texwe)
	{
		if (line[2] != NADA || !(info->tex.path_we = path_tex(line, info, 2)))
			clean_exit(info, "Textura oeste incorrecta\n", 1);
		info->check.texwe = 1;
        return (1);
	}
    else if (!ft_strncmp(line, "WE", 2) && info->check.texwe)
        clean_exit(info, "Identificador de textura oeste duplicado\n", 1);
	else if (!ft_strncmp(line, "EA", 2) && !info->check.texea)
	{
		if (line[2] != NADA || !(info->tex.path_ea = path_tex(line, info, 2)))
			clean_exit(info, "Textura este incorrecta\n", 1);
		info->check.texea = 1;
        return (1);
	}
    else if (!ft_strncmp(line, "EA", 2) && info->check.texea)
        clean_exit(info, "Identificador de textura este duplicado\n", 1);
    return (0);
}

void		info_tex(char *line, t_cub *info)
{
	int done;
    
    remove_spaces(&line);
	done = vertical_text(line, info) || horizontal_text(line, info);
	if (!done && !ft_strncmp(line, "S", 1) && !info->check.texsp)
	{
		if (line[1] != NADA || !(info->tex.path_sp = path_tex(line, info, 1)))
			clean_exit(info, "Textura sprite incorrecta\n", 1);
		info->check.texsp = 1;
	}
    else if (!done && !ft_strncmp(line, "S", 1) && info->check.texsp)
        clean_exit(info, "Identificador de textura sprite duplicado\n", 1);
}

int     is_texture(char *line)
{
    char *aux;

    if ((aux = ft_strchr(line, 'N')) && aux[1] == 'O')
        return (1);
    else if ((aux = ft_strchr(line, 'S')) && aux[1] == 'O')
        return (1);
    else if ((aux = ft_strchr(line, 'W')) && aux[1] == 'E')
        return (1);
    else if ((aux = ft_strchr(line, 'E')) && aux[1] == 'A')
        return (1);
    else if ((aux = ft_strchr(line, 'S')))
        return (1);

    return (0);
}