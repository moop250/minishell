/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/24 17:01:09 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_env(char **in, t_core *core)
{
	t_envparam	*tmp;

	if (in[1])
	{
		ms_printerror(3, NULL);
		return (1);
	}
	tmp = core->env->rawenvs;
	while (tmp)
	{
		if (tmp->value && tmp->base)
			ft_printf_fd(STDOUT_FILENO, "%s%s=%s%s\n", ORANGE,
				tmp->name, tmp->value, CLEAR);
		tmp = tmp->next;
	}
	return (0);
}
