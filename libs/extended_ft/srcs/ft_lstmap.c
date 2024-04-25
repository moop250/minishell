/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:36:59 by hlibine           #+#    #+#             */
/*   Updated: 2023/10/27 18:20:41 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void*))
{
	t_list	*out;
	t_list	*obj;

	if (!lst || !f || !del)
		return (NULL);
	out = NULL;
	while (lst)
	{
		obj = ft_lstnew(f(lst->content));
		if (!obj)
		{
			ft_lstclear(&out, del);
			return (NULL);
		}
		ft_lstadd_back(&out, obj);
		lst = lst->next;
	}
	return (out);
}
