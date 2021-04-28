/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:55:15 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/28 19:51:16 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b2;
	size_t			i;

	i = 0;
	b2 = (unsigned char *)b;
	while (i < len)
	{
		b2[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	char	*aux;
	size_t	i;

	aux = (char *)s;
	i = 0;
	while (i < n)
	{
		aux[i] = 0;
		i++;
	}
}

char	*ft_swap(char *l, char *buf)
{
	char	*temp;

	temp = ft_strjoin(l, buf);
	free(l);
	l = ft_strdup(temp);
	free(temp);
	temp = NULL;
	return (l);
}
