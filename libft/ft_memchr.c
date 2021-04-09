/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:06:11 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/27 18:26:46 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	aux;
	size_t			i;

	str = (unsigned char *)s;
	aux = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == aux)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
