/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:22:17 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/26 17:55:29 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	aux;

	aux = (char)c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == aux)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
