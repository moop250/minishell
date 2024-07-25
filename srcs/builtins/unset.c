/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:57:39 by pberset           #+#    #+#             */
/*   Updated: 2024/07/24 17:24:50 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_unset(char **in)
{
	t_envparam	*tmp;
	int			i;

	i = 0;
	while (in[++i])
	{
		tmp = findenv(in[i]);
		if (tmp)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			gfree(tmp->name);
			gfree(tmp->value);
			gfree(tmp);
		}
	}
	return (0);
}
