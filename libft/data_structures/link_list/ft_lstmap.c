/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:41:10 by njennes           #+#    #+#             */
/*   Updated: 2021/11/09 17:08:34 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_clearall(t_list **first, void (*del)(void *))
{
	ft_lstclear(first, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*last;
	t_list	*next;

	if (!lst || !f)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	if (!first)
		return (NULL);
	last = first;
	while (lst->next)
	{
		lst = lst->next;
		next = ft_lstnew(f(lst->content));
		if (!next)
			return (ft_clearall(&first, del));
		ft_lstadd_back(&last, next);
		last = next;
	}
	return (first);
}
