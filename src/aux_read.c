/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:49:15 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 19:30:50 by igomez-p         ###   ########.fr       */
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

/*void    free_stc_exit(t_cub *c, char *txt, char *stc)
{
    free(stc);
    clean_exit(c, txt, 1);
}*/