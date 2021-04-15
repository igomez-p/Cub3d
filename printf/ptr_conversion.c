/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:38:37 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 13:37:10 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft//printf.h"

static void	flag_width_ptr(t_//printf *lst, char *str)
{
	char	*new_str;

	new_str = ft_strdup("0x");
	new_str = ft_swap(new_str, str);
	if (lst->activate_flag[1] == '1' && lst->activate_flag[0] == '0')
	{
		ft_putstr_fd("0x", 1);
		putchar_width0(lst, '0', 'w', ft_strlen(new_str));
	}
	else if (lst->activate_flag[1] == '0' && lst->activate_flag[0] == '0')
	{
		putchar_width0(lst, ' ', 'w', ft_strlen(new_str));
		ft_putstr_fd("0x", 1);
	}
	if (lst->activate_flag[0] == '1')
		ft_putstr_fd(new_str, 1);
	else
		ft_putstr_fd(str, 1);
	lst->nbytes += ft_strlen(new_str);
	if (lst->activate_flag[0] == '1')
		putchar_width0(lst, ' ', 'w', ft_strlen(new_str));
	lst->width = 0;
	free(new_str);
}

static void	flag_precision0(t_//printf *lst, char *hex, char *new_hex)
{
	while ((lst->precision - (int)ft_strlen(hex)) >= 1)
	{
		new_hex = ft_swap(new_hex, "0");
		lst->precision--;
	}
	new_hex = ft_swap(new_hex, hex);
	if (lst->precision < lst->width)
		flag_width_ptr(lst, &new_hex[2]);
	else
	{
		ft_putstr_fd(new_hex, 1);
		lst->nbytes += ft_strlen(new_hex);
	}
}

static void	flag_precision(t_//printf *lst, char *hex)
{
	char	*new_hex;

	new_hex = ft_strdup("0x");
	lst->activate_flag[1] = (lst->activate_flag[1] == '1') ? '0' : '0';
	if (lst->precision <= (int)ft_strlen(hex))
		flag_width_ptr(lst, hex);
	else
	{
		if (lst->activate_flag[3] == '0' || (lst->activate_flag[3] == '1' &&
		(lst->width <= (int)ft_strlen(hex) || lst->width <= lst->precision)))
		{
			ft_putstr_fd(new_hex, 1);
			putchar_width0(lst, '0', 'p', (int)ft_strlen(hex));
			ft_putstr_fd(hex, 1);
			lst->nbytes += (ft_strlen(hex) + ft_strlen(new_hex));
		}
		else
			flag_precision0(lst, hex, new_hex);
	}
}

void		ft_conversion_ptr(t_//printf *lst, unsigned long ptr)
{
	char	*memo;

	memo = ft_itohex(ptr, 'x');
	if (!is_activate_flag(lst) || !flag_conversion_int(lst, memo))
	{
		ft_putstr_fd("0x", 1);
		if (!ptr && lst->activate_flag[2] == '1')
		{
			free(memo);
			memo = ft_strdup("");
		}
		ft_putstr_fd(memo, 1);
		lst->nbytes += (ft_strlen(memo) + ft_strlen("0x"));
	}
	else
	{
		if (lst->activate_flag[2] == '1')
			!ptr ? flag_precision(lst, "") : flag_precision(lst, memo);
		else if (lst->activate_flag[3] == '1')
			flag_width_ptr(lst, memo);
	}
	free(memo);
	initialize(lst);
}
