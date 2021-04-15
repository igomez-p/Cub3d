/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:54:10 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 12:06:07 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft//printf.h"

static int	flag_conversion(t_//printf *lst, char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	if (!ft_strncmp(lst->activate_flag, "0100", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1100", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0110", 4) && lst->precision >= len)
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1000", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1010", 4) && lst->precision >= len)
		return (0);
	return (1);
}

static void	putchar_width(t_//printf *lst, char c, char *str)
{
	int w;

	if (lst->width > (int)ft_strlen(str))
		w = lst->width - ft_strlen(str) + 1;
	else
		w = 0;
	while (w > 1)
	{
		ft_putchar_fd(c, 1);
		lst->nbytes++;
		w--;
	}
}

static void	flag_width(t_//printf *lst, char *str)
{
	if (lst->activate_flag[1] == '1' && lst->activate_flag[0] == '0')
		putchar_width(lst, '0', str);
	else if (lst->activate_flag[1] == '0' && lst->activate_flag[0] == '0')
		putchar_width(lst, ' ', str);
	ft_putstr_fd(str, 1);
	lst->nbytes += ft_strlen(str);
	if (lst->activate_flag[0] == '1')
		putchar_width(lst, ' ', str);
	lst->width = 0;
}

static void	flag_precision(t_//printf *lst, char *str)
{
	char new_str[lst->precision];

	if (lst->precision >= (int)ft_strlen(str))
	{
		if (lst->activate_flag[3] == '1')
			flag_width(lst, str);
		else
		{
			ft_putstr_fd(str, 1);
			lst->nbytes += ft_strlen(str);
		}
	}
	else
	{
		fill_str(str, new_str, lst->precision);
		if (lst->activate_flag[3] == '1')
			flag_width(lst, new_str);
		else
		{
			ft_putstr_fd(new_str, 1);
			lst->nbytes += ft_strlen(new_str);
		}
	}
	lst->precision = 0;
}

void		ft_conversion_string(t_//printf *lst, char *str)
{
	if (!str)
		str = ft_strdup("(null)");
	if (!is_activate_flag(lst) || !flag_conversion(lst, str))
	{
		ft_putstr_fd(str, 1);
		lst->nbytes += ft_strlen(str);
	}
	else
	{
		if (lst->activate_flag[2] == '1')
			flag_precision(lst, str);
		else if (lst->activate_flag[3] == '1')
			flag_width(lst, str);
	}
	initialize(lst);
}
