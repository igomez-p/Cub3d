/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:51:14 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/22 13:33:11 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	len(int nb)
{
	int cont;

	cont = 1;
	while ((nb / 10) > 0)
	{
		cont++;
		nb = nb / 10;
	}
	return (cont);
}

static int	pow10(int l)
{
	int cont;

	cont = 1;
	while (l != 1)
	{
		cont *= 10;
		l--;
	}
	return (cont);
}

static void	ft_print(int div, int n, int fd)
{
	char	a;

	while (div >= 1)
	{
		a = (n / div) + 48;
		write(fd, &a, 1);
		n %= div;
		div /= 10;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	int			div;
	long int	n2;

	n2 = n;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n2 *= (-1);
	}
	if (n2 >= 0)
	{
		div = pow10(len(n2));
		ft_print(div, n2, fd);
	}
}
