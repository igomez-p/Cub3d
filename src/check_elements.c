#include "../inc/cub.h"

int	error_tex_elements(char *line)
{
	int i;
	int extension;

	extension = 0;
	i = 0;
	while (line[i] && line[i] != NADA)
		i++;
	
	if (line[i-4] == '.' && line[i-3] == 'x' && line[i-2] == 'p' && line[i-1] == 'm')
		extension = 1;
	
	while (line[i] && line[i] == NADA)
		i++;
	
	if ((line[i-1] == NADA && line[i] && extension) || !extension)
		return (1);
	return (0);
}

int error_res_elements(char *line)
{
    int i;

    i = 0;
    if (line[i] == 'R')
        i++;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == NADA))
        i++;

    if (line[i])
        return (1);
    return (0);
}

void error_rgb_elements(t_cub *info, char *line)
{
    int i;

    i = 0;
    if (line[i] == 'F' || line[i] == 'C')
        i++;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == NADA || line[i] == ','))
    {
        if (line[i] == ',' && !ft_isdigit(line[i+1]))
            clean_exit(info, "Formato RGB invalido\n", 1);
        i++;
    }

    if (line[i])
    {
        if (line[0] == 'F')
        {
            //free(line);
            clean_exit(info, "Caracteres invalidos en color de suelo\n", 1);
        }
        else if (line[0] == 'C')
            clean_exit(info, "Caracteres invalidos en color de techo\n", 1);
    }
}