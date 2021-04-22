
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:55:21 by igomez-p          #+#    #+#             */
/*   Updated: 2021/04/21 19:55:21 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int         ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sig;

	num = 0;
	sig = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
	{
		sig = 1;
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (num * sig > 2147483647)
		return (-1);
	return (num * sig);
}