/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:36:26 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/26 19:03:13 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;

	if (!s)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ((int)len + 1));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, len);
	if (start <= (unsigned int)ft_strlen(s))
		ft_strlcpy(new, s + start, len + 1);
	return (new);
}
