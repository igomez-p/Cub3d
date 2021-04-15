/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_//printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:16:10 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/13 16:53:52 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft//printf.h"

char	*ft_minisplit(char *s)
{
	int		p;
	int		k;
	char	*temp;

	p = 0;
	while (s[p] && s[p] != '%')
		p++;
	if (!(temp = (char *)malloc(sizeof(char) * (p + 1))))
		return (NULL);
	k = 0;
	while (k != p)
	{
		temp[k] = s[k];
		k++;
	}
	temp[k] = '\0';
	return (temp);
}

void	ft_write(t_//printf *lst, char *str)
{
	char	*aux;
	char	*temp;
	char	*temp2;
	int		i;

	while ((aux = ft_strchr(str, '%')))
	{
		temp2 = ft_minisplit(str);
		ft_putstr_fd(temp2, 1);
		lst->nbytes += ft_strlen(temp2);
		free(temp2);
		temp = ft_strdup(&aux[1]);
		i = ft_activate_flag(lst, temp) + 1;
		if (temp[i - 1] == '%' || temp[0] == '%')
			ft_conversion_char(lst, '%');
		else
			type_conversion(lst, temp[i - 1]);
		str = ft_strdup(&temp[i]);
		free(temp);
	}
	ft_putstr_fd(str, 1);
	lst->nbytes += ft_strlen(str);
}

int		ft_//printf(const char *str, ...)
{
	t_//printf	lista;
	va_list		va_aux;
	char		*aux_str;

	aux_str = (char *)str;
	if (!ft_strchr(aux_str, '%'))
	{
		ft_putstr_fd(aux_str, 1);
		return (ft_strlen(aux_str));
	}
	initialize(&lista);
	lista.nbytes = 0;
	va_start(lista.args, str);
	va_copy(va_aux, lista.args);
	ft_write(&lista, aux_str);
	va_end(lista.args);
	va_end(va_aux);
	return (lista.nbytes);
}
