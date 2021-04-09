/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:57:33 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/27 21:13:24 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char			*ft_strnstr(const char *haystack, const char *needle, size_t l)
{
	size_t	len_ned;
	size_t	k;

	k = 0;
	len_ned = ft_strlen(needle);
	if (ft_strlen(haystack) < len_ned)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	while ((k + len_ned) <= l && *haystack)
	{
		if (ft_strncmp(haystack, needle, len_ned) == 0)
			return ((char *)haystack);
		haystack++;
		k++;
	}
	return (NULL);
}
