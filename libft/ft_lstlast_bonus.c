/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:35:43 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/18 18:20:27 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		size;
	t_list	*aux;

	size = ft_lstsize(lst);
	aux = lst;
	size--;
	while (size > 0)
	{
		aux = aux->next;
		size--;
	}
	return (aux);
}
