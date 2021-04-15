/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 11:01:41 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/16 17:41:59 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft//printf.h"

int		int_leng(long int n, int base)
{
	int cont;

	cont = 0;
	if (n <= 0)
	{
		cont++;
		n *= (-1);
	}
	while (n > 0)
	{
		cont++;
		n /= base;
	}
	return (cont);
}

char	*ft_swap(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strdup(temp);
	free(temp);
	return (s1);
}

void	fill_str(const char *str, char *dest, int x)
{
	int i;

	i = 0;
	while (str[i] && i < x)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_reverse(char *n)
{
	char			aux[ft_strlen(n)];
	int				i;
	int				len;

	i = 0;
	len = ft_strlen(n) - 1;
	while (len >= 0)
	{
		aux[i] = n[len];
		i++;
		len--;
	}
	aux[i] = '\0';
	len = 0;
	while (aux[len])
	{
		n[len] = aux[len];
		len++;
	}
}
