/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:32:27 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 13:07:19 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	putchar_width(t_printf *lst, char c)
{
	while (lst->width > 1)
	{
		ft_putchar_fd(c, 1);
		lst->nbytes++;
		lst->width--;
	}
}

static void	flag_minus_width(t_printf *lst, char c)
{
	ft_putchar_fd(c, 1);
	lst->nbytes++;
	putchar_width(lst, ' ');
	lst->width = 0;
}

static void	flag_width(t_printf *lst, char c)
{
	if (lst->activate_flag[1] == '1')
		putchar_width(lst, '0');
	else
		putchar_width(lst, ' ');
	ft_putchar_fd(c, 1);
	lst->nbytes++;
	lst->width = 0;
}

static int	flag_conversion(t_printf *lst)
{
	if (!ft_strncmp(lst->activate_flag, "0100", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0010", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0110", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1000", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1100", 4))
		return (0);
	return (1);
}

void		ft_conversion_char(t_printf *lst, char c)
{
	if (!is_activate_flag(lst) || !flag_conversion(lst))
	{
		ft_putchar_fd(c, 1);
		lst->nbytes++;
	}
	else
	{
		if (lst->activate_flag[0] == '1' && lst->activate_flag[3] == '1')
			flag_minus_width(lst, c);
		else if (lst->activate_flag[3] == '1')
			flag_width(lst, c);
		else
		{
			ft_putchar_fd(c, 1);
			lst->nbytes++;
		}
	}
	initialize(lst);
}
