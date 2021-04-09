/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:49:19 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/26 15:00:21 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_reverse(char *n)
{
	char			aux[30];
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

static int	int_leng(long int n)
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
		n /= 10;
	}
	return (cont);
}

char		*ft_itoa(int n)
{
	char			*num;
	unsigned int	i;
	long int		n2;

	n2 = n;
	if (!(num = (char *)malloc(sizeof(char) * (int_leng(n2) + 1))))
		return (NULL);
	i = 0;
	n2 = (n2 < 0) ? n2 *= (-1) : n2;
	while (n2 >= 10)
	{
		num[i] = (n2 % 10) + 48;
		n2 /= 10;
		i++;
	}
	num[i] = n2 + 48;
	i++;
	if (n < 0)
	{
		num[i] = '-';
		i++;
	}
	num[i] = '\0';
	ft_reverse(num);
	return (num);
}
