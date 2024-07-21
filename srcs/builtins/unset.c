/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:57:39 by pberset           #+#    #+#             */
/*   Updated: 2024/07/22 00:02:45 by hlibine          ###   LAUSANNE.ch       */
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
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			gfree(tmp->name);
			gfree(tmp->value);
			gfree(tmp);
		}
	}
	return (0);
}
