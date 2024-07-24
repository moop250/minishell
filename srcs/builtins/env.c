/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/24 09:56:28 by pberset          ###   ########.fr       */
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
		if (tmp->value)
			ft_printf_fd(core->ms_stdout, "%s%s=%s%s\n", ORANGE,
				tmp->name, tmp->value, CLEAR);
		tmp = tmp->next;
	}
	return (0);
}
