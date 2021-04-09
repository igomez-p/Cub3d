/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:01:41 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 15:57:30 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		putchar_width0(t_printf *lst, char c, char p, int len)
{
	int w;

	if (p == 'p')
		w = lst->precision - len + 1;
	else if (lst->width > len)
		w = lst->width - len + 1;
	else
		w = 0;
	while (w > 1)
	{
		ft_putchar_fd(c, 1);
		lst->nbytes++;
		w--;
	}
}

void		flag_width_int(t_printf *lst, char *str)
{
	if (lst->activate_flag[1] == '1' && lst->activate_flag[0] == '0')
	{
		if (str[0] == '-')
		{
			ft_putchar_fd('-', 1);
			lst->width--;
			lst->nbytes++;
			str++;
		}
		putchar_width0(lst, '0', 'w', (int)ft_strlen(str));
	}
	else if (lst->activate_flag[1] == '0' && lst->activate_flag[0] == '0')
		putchar_width0(lst, ' ', 'w', (int)ft_strlen(str));
	ft_putstr_fd(str, 1);
	lst->nbytes += ft_strlen(str);
	if (lst->activate_flag[0] == '1')
		putchar_width0(lst, ' ', 'w', (int)ft_strlen(str));
	lst->width = 0;
}

static void	flag_precision0(t_printf *lst, char *num, long int n, int b)
{
	if (n < 0)
	{
		num = ft_swap(num, "-");
		n = n * (-1);
	}
	while ((lst->precision - int_leng(n, b)) >= 1)
	{
		num = ft_swap(num, "0");
		lst->precision--;
	}
	num = lst->d ? ft_swap(num, ft_itoa(n)) : ft_swap(num, ft_itoa_unsig(n));
	if (lst->precision < lst->width)
		flag_width_int(lst, num);
	else
	{
		ft_putstr_fd(num, 1);
		lst->nbytes += ft_strlen(num);
	}
}

static void	flag_precision(t_printf *lst, long int n, int b)
{
	char	*nu;
	int		leng;

	lst->activate_flag[1] = (lst->activate_flag[1] == '1') ? '0' : '0';
	leng = (n < 0) ? ft_strlen(ft_itoa(n * -1)) : int_leng(n, b);
	if (lst->precision <= leng && lst->activate_flag[3] == '1' && n)
	{
		nu = lst->d ? ft_strdup(ft_itoa(n)) : ft_strdup(ft_itoa_unsig(n));
		flag_width_int(lst, nu);
	}
	else
	{
		if (lst->activate_flag[3] == '0' || (lst->activate_flag[3] == '1' &&
			(lst->width <= int_leng(n, b) || lst->width <= lst->precision)))
		{
			if (n < 0)
				putchar_width0(lst, '-', 'p', lst->precision - 1);
			n *= (n < 0) ? (-1) : 1;
			putchar_width0(lst, '0', 'p', int_leng(n, b));
			ft_putnbr_fd(n, 1);
			lst->nbytes += int_leng(n, b);
		}
		else
			flag_precision0(lst, ft_strdup(""), n, b);
	}
}

void		ft_conversion_int(t_printf *lst, long int num, char c)
{
	char *num_str;

	if (!num && lst->activate_flag[2] == '1')
		num_str = ft_strdup(" ");
	else
		num_str = (c == 'u') ? ft_itoa_unsig(num) : ft_itoa(num);
	if (!is_activate_flag(lst) || !flag_conversion_int(lst, num_str))
	{
		(!num && !is_activate_flag(lst)) ? ft_putstr_fd("0", 1) :
											ft_putstr_fd(num_str, 1);
		lst->nbytes += ft_strlen(num_str);
	}
	else
	{
		if (lst->activate_flag[2] == '1')
			(!lst->precision && !num && lst->width >= 0) ?
				putchar_width0(lst, ' ', 'w', 0) : flag_precision(lst, num, 10);
		else if (lst->activate_flag[3] == '1')
		{
			num_str = lst->d ? ft_itoa(num) : ft_itoa_unsig(num);
			flag_width_int(lst, num_str);
		}
	}
	initialize(lst);
}
