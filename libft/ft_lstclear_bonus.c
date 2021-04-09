/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:19:36 by igomez-p          #+#    #+#             */
/*   Updated: 2019/11/15 11:32:50 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*act;
	t_list	*sig;

	if (*lst != NULL)
	{
		act = *lst;
		while (act)
		{
			sig = act->next;
			del(act->content);
			free(act);
			act = sig;
		}
		*lst = NULL;
	}
}
