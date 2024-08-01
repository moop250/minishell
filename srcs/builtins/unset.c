/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:57:39 by pberset           #+#    #+#             */
/*   Updated: 2024/08/01 21:08:42 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_unset(char **in)
{
	t_envparam	*tmp;
	t_envparam	**head;
	int			i;

	i = 0;
	head = &get_core()->env->rawenvs;
	while (in[++i])
	{
		tmp = findenv(in[i]);
		if (tmp)
		{
			gfree(tmp->name);
			gfree(tmp->value);
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				(*head) = (*head)->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			gfree(tmp);
		}
	}
	return (0);
}
