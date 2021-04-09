/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 13:27:06 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 16:12:38 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_else(t_printf *ls, char *s, int i)
{
	if (s[i] == ls->flags[2])
	{
		ls->activate_flag[2] = '1';
		if (ft_isdigit(s[i + 1]) || s[i + 1] == ls->flags[3])
		{
			i++;
			ls->precision = ft_isdigit(s[i]) ? s[i] - 48 :
												va_arg(ls->args, int);
			if (ls->precision < 0)
				ls->activate_flag[2] = '0';
		}
	}
	else
	{
		if (ls->activate_flag[2] == '1')
			ls->precision = !ls->precision ? s[i] - 48 :
											(ls->precision * 10) + s[i] - 48;
		else
		{
			ls->activate_flag[3] = '1';
			ls->width = !ls->width ? s[i] - 48 : (ls->width * 10) + s[i] - 48;
		}
	}
	return (i);
}

int			ft_activate_flag(t_printf *ls, char *s)
{
	int		i;

	i = 0;
	while (search_flag(ls, s[i]) || ft_isdigit(s[i]))
	{
		if (s[i] == ls->flags[0])
			ls->activate_flag[0] = '1';
		else if (s[i] == ls->flags[1] && !ft_isdigit(s[i - 1]))
			ls->activate_flag[1] = '1';
		else if (s[i] == ls->flags[3])
		{
			ls->activate_flag[3] = '1';
			ls->width = va_arg(ls->args, int);
			if (ls->width < 0)
			{
				ls->width *= (-1);
				ls->activate_flag[0] = '1';
			}
		}
		else
			i = ft_else(ls, s, i);
		i++;
	}
	return (i);
}

int			flag_conversion_int(t_printf *lst, char *n)
{
	int	len;
	int	x;
	int ok;

	len = (int)ft_strlen(n);
	ok = (lst->precision < len && !ft_strncmp(n, "0", 1)) ? 1 : 0;
	if (!ft_strncmp(lst->activate_flag, "1000", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0100", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1100", 4))
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0110", 4) && ok)
		return (0);
	if (!ft_strncmp(lst->activate_flag, "0010", 4) && ok)
		return (0);
	if (!ft_strncmp(lst->activate_flag, "1010", 4) && ok)
		return (0);
	x = !(lst->p) ? len : (len + 2);
	if (ok && lst->width < x)
		return (0);
	return (1);
}
