
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:55:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/21 19:55:02 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

static int	cont_char(char const *s, char c)
{
	int i;
	int cont;

	i = 0;
	cont = 0;
	if (s[0] && s[0] != c)
		cont++;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			cont++;
		i++;
	}
	return (cont);
}

static char	*ft_word(char const *s, char c, int i)
{
	int		p;
	int		k;
	char	*w;

	p = i;
	while (s[i] && s[i] != c)
		i++;
	w = (char *)malloc(sizeof(char) * ((i - p) + 1));
	if (!w)
		return (NULL);
	k = 0;
	while (p != i)
	{
		w[k] = s[p];
		k++;
		p++;
	}
	w[k] = '\0';
	return (w);
}

char		**ft_split(char const *s1, char c)
{
	char	**m;
	int		i;
	int		k;

	if (!s1)
		return (NULL);
	m = (char **)malloc(sizeof(char *) * (cont_char(s1, c) + 1));
	if (!m)
		return (NULL);
	i = 0;
	k = 0;
	while (i <= (int)ft_strlen(s1) && cont_char(s1, c))
	{
		if (ft_strlen(ft_word(s1, c, i)))
		{
			m[k] = ft_word(s1, c, i);
			i += (ft_strlen(m[k]) + 1);
			k++;
		}
		else
			i++;
	}
	m[k] = NULL;
	return (m);
}