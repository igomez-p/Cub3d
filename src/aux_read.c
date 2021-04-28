/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:49:15 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 20:44:19 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int ft_isspace(char c)
{
    return (c == SPACE || c == '\t');
}

int all_textures(t_cub *c)
{
    return (c->check.texno && c->check.texso && c->check.texwe
        && c->check.texea && c->check.texsp);
}

void    free_str_exit(t_cub *c, char *txt, char *str)
{
    if (str != NULL)
        free(str);
    clean_exit(c, txt, 1);
}

void    check_open_tex(t_cub *c)
{
    int fd;

    fd = open(c->tex.path_no, O_RDONLY);
    if (fd < 0)
        clean_exit(c, "Fail to open texture\n", 1);
    close(fd);
    fd = open(c->tex.path_so, O_RDONLY);
    if (fd < 0)
        clean_exit(c, "Fail to open texture\n", 1);
    close(fd);
    fd = open(c->tex.path_we, O_RDONLY);
    if (fd < 0)
        clean_exit(c, "Fail to open texture\n", 1);
    close(fd);
    fd = open(c->tex.path_ea, O_RDONLY);
    if (fd < 0)
        clean_exit(c, "Fail to open texture\n", 1);
    close(fd);
    fd = open(c->tex.path_sp, O_RDONLY);
    if (fd < 0)
        clean_exit(c, "Fail to open texture\n", 1);
    close(fd);
}