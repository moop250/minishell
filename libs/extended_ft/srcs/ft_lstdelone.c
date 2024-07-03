/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:29:46 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/03 20:12:47 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	gfree(lst->content);
	gfree(lst);
	return ;
}
