/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:29:02 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/26 19:04:20 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	while (s1[pos] && s2[pos] && s1[pos] == s2[pos] && pos < n)
		pos++;
	if (s1[pos] != s2[pos] && pos < n)
		return (((unsigned char)s1[pos] - (unsigned char)s2[pos]));
	return (0);
}
