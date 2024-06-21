/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:28:07 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l_new;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	l_new = NULL;
	while (lst)
	{
		new_elem = malloc(sizeof(t_list));
		if (!new_elem)
		{
			ft_lstclear(&l_new, del);
			return (NULL);
		}
		new_elem->content = f(lst->content);
		new_elem->next = NULL;
		ft_lstadd_back(&l_new, new_elem);
		lst = lst->next;
	}
	return (l_new);
}
