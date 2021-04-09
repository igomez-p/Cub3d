/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfstruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:52:29 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 16:26:17 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		initialize(t_printf *new)
{
	fill_str("cspdiuxX", (char *)new->conversions, (int)ft_strlen("cspdiuxX"));
	fill_str("-0.*", (char *)new->flags, (int)ft_strlen("-0.*"));
	fill_str("0000", new->activate_flag, (int)ft_strlen("0000"));
	new->precision = 0;
	new->width = 0;
	new->c = 0;
	new->s = NULL;
	new->p = 0;
	new->d = 0;
	new->u = 0;
	new->x = 0;
}

int			search_flag(t_printf *list, char c)
{
	int	i;

	i = 0;
	while (list->flags[i])
	{
		if (list->flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		type_conversion(t_printf *list, char c)
{
	if (c == 'c')
		ft_conversion_char(list, list->c = va_arg(list->args, int));
	else if (c == 's')
		ft_conversion_string(list, list->s = va_arg(list->args, char *));
	else if (c == 'p')
		ft_conversion_ptr(list, list->p = va_arg(list->args, unsigned long));
	else if (c == 'd' || c == 'i')
		ft_conversion_int(list, list->d = va_arg(list->args, int), 'i');
	else if (c == 'u')
	{
		list->u = va_arg(list->args, unsigned long int);
		ft_conversion_int(list, list->u, 'u');
	}
	else if (c == 'x' || c == 'X')
	{
		list->x = va_arg(list->args, unsigned long int);
		ft_conversion_hex(list, list->x, c);
	}
}

int			is_activate_flag(t_printf *lst)
{
	if (lst->activate_flag[0] == '1')
		return (1);
	if (lst->activate_flag[1] == '1')
		return (1);
	if (lst->activate_flag[2] == '1')
		return (1);
	if (lst->activate_flag[3] == '1')
		return (1);
	return (0);
}
