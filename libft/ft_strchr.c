/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:19:13 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/26 13:38:37 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	aux;
	int		pos;

	aux = (char)c;
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == aux)
			return ((char *)&s[pos]);
		pos++;
	}
	if (!s[pos] && aux == '\0')
		return ((char *)&s[pos]);
	return (NULL);
}
