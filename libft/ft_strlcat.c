/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:47:11 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/27 18:36:05 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	lend;

	lend = 0;
	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	while (dst[lend] && lend < dstsize)
		lend++;
	l = lend;
	while (src[lend - l] && (lend + 1) < dstsize)
	{
		dst[lend] = src[lend - l];
		lend++;
	}
	dst[lend] = '\0';
	return (ft_strlen(src) + l);
}
