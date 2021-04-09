/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 11:20:20 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 16:23:01 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_itohex(unsigned long num, char c)
{
	char			*nhex;
	int				i;
	unsigned long	temp;

	nhex = malloc(sizeof(char) * (int_leng(num, 16) + 1));
	if (!nhex)
		return (NULL);
	i = 0;
	temp = num % 16;
	nhex[i] = (temp < 10) ? temp + 48 : (temp + c - 33);
	i++;
	while ((num /= 16) != 0)
	{
		temp = num % 16;
		if (temp < 10)
			nhex[i] = temp + 48;
		else if (temp < 16)
			nhex[i] = (c == 'x') ? temp + 87 : temp + 55;
		i++;
	}
	nhex[i] = '\0';
	ft_reverse(nhex);
	return (nhex);
}

static void	flag_precision0(t_printf *lst, char *hex, char *new_hex)
{
	while ((lst->precision - (int)ft_strlen(hex)) >= 1)
	{
		new_hex = ft_swap(new_hex, "0");
		lst->precision--;
	}
	new_hex = ft_swap(new_hex, hex);
	if (lst->precision < lst->width)
		flag_width_int(lst, new_hex);
	else
	{
		ft_putstr_fd(new_hex, 1);
		lst->nbytes += ft_strlen(hex);
	}
}

static void	flag_precision(t_printf *lst, char *hex)
{
	char	*new_hex;

	new_hex = ft_strdup("");
	lst->activate_flag[1] = (lst->activate_flag[1] == '1') ? '0' : '0';
	if (lst->precision <= (int)ft_strlen(hex) && lst->activate_flag[3] == '1')
		flag_width_int(lst, hex);
	else
	{
		if (lst->activate_flag[3] == '0' || (lst->activate_flag[3] == '1' &&
		(lst->width <= (int)ft_strlen(hex) || lst->width <= lst->precision)))
		{
			putchar_width0(lst, '0', 'p', (int)ft_strlen(hex));
			ft_putstr_fd(hex, 1);
			lst->nbytes += ft_strlen(hex);
		}
		else
			flag_precision0(lst, hex, new_hex);
	}
}

static void	ft_else(t_printf *lst, unsigned int num, char *hex)
{
	if (lst->activate_flag[2] == '1')
	{
		if (!lst->precision && !num)
		{
			lst->activate_flag[1] = lst->activate_flag[1] == '1' ? '0' : '0';
			flag_width_int(lst, " ");
		}
		else
			flag_precision(lst, hex);
	}
	else if (lst->activate_flag[3] == '1')
		flag_width_int(lst, hex);
}

void		ft_conversion_hex(t_printf *lst, unsigned int num, char c)
{
	char	*hex;

	hex = ft_itohex(num, c);
	if (!is_activate_flag(lst) || !flag_conversion_int(lst, hex))
	{
		if (!num && lst->activate_flag[2] == '1')
			ft_putstr_fd("", 1);
		else
		{
			ft_putstr_fd(hex, 1);
			lst->nbytes += ft_strlen(hex);
		}
	}
	else
		ft_else(lst, num, hex);
	free(hex);
	initialize(lst);
}
