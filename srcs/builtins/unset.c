/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:57:39 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 11:47:18 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_unset(char **in, t_core *core)
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
	core->exit_status = 0;
}
